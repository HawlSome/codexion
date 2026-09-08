*This project has been created as part of the 42 curriculum by varandri.*

# Codexion

## Description

Codexion is a POSIX-threads simulation of the classic dining‑philosophers problem,
reskinned as coders racing to compile quantum code before burning out. `number_of_coders`
coders sit around a circular co-working hub; between every pair of neighbors sits one
shared USB dongle. To compile, a coder must hold both of their neighboring dongles at
once. After compiling, a coder debugs, then refactors, then immediately tries to compile
again. A dedicated monitor thread watches every coder's deadline and stops the simulation
the instant one of them fails to start compiling within `time_to_burnout` milliseconds of
their last compile (or of the simulation start).

The simulation ends either when a coder burns out, or when every coder has completed at
least `number_of_compiles_required` compiles.

### Implementation overview

- **One thread per coder** (`pthread_create`), plus one **monitor thread**, plus
  short-lived **cooldown timer threads** (one per dongle release).
- Coders form a linked ring; each coder holds pointers to its `l_dongle` and
  `r_dongle`, each dongle shared with a neighbor. A single coder has
  `l_dongle == r_dongle`.
- Each dongle owns a **priority queue** (binary min-heap) of pending requests.
- Coder routine: register in both queues → wait until served → compile → release
  both dongles into cooldown → debug → refactor → repeat until quota reached or
  the simulation is stopped.
- The **monitor** polls coder vitals every 1 ms, detects burnout, and stops
  everything. When all coder threads have finished, `main` joins them, stops the
  monitor, and frees every allocation.
- Timestamps come from `gettimeofday()`, relative to a start time captured at
  launch. No global variables — all state travels through a shared `t_config`
  and per-thread argument structs.

## Instructions

### Build

```sh
make
```

This compiles the sources in `coders/` with `cc -Wall -Wextra -Werror -pthread` and
produces the `codexion` binary. `clean`, `fclean` and `re` rules are also available.

### Clean object files

```sh
make clean
```

### Clean object files and binary

```sh
make fclean
```

### Recompile

```sh
make re
```

### Run

```sh
./codexion number_of_coders time_to_burnout time_to_compile time_to_debug \
           time_to_refactor number_of_compiles_required dongle_cooldown scheduler
```

Example:

```sh
./codexion 5 800 200 200 200 3 100 fifo
```

- `number_of_coders`: number of coders (and dongles), must be between 1 and 300.
- `time_to_burnout`, `time_to_compile`, `time_to_debug`, `time_to_refactor`,
  `dongle_cooldown`: all in milliseconds, must be non-negative integers.
- `number_of_compiles_required`: non-negative integer; simulation stops once every
  coder has reached this many compiles.
- `scheduler`: arbitration policy for dongle access, must be `fifo` or `edf`.

All 8 arguments are mandatory. Invalid input (missing/extra arguments, negative or
non-numeric values, or an unrecognized scheduler) is rejected with an error message and
the program exits without running the simulation.

Each state change is logged as:

```
timestamp_in_ms coder_id has taken a dongle
timestamp_in_ms coder_id is compiling
timestamp_in_ms coder_id is debugging
timestamp_in_ms coder_id is refactoring
timestamp_in_ms coder_id burned out
```

## Resources

- `man pthread_mutex_init`, `man pthread_cond_wait`, `man pthread_cond_timedwait`,
  `man gettimeofday`
- [Coffman conditions](https://faq.computersciencewiki.org/index.php/home/article/coffman-conditions): Overview of Coffman conditions and deadlocks.
- [Codexion Visualizer](https://codexion-visualizer.sacha-dev.me/): To visualize the simulation and understand it.
- [Programming with Threads](https://www.youtube.com/playlist?list=PL9IEJIKnBJjFZxuqyJ9JqVYmuFZHr7CFM): Complete tutorials about threading in C.

### AI Usage
- **Thread explanations**: How threads work, how they share the same data, and how to manipulate those
  safely.
- **Documentation**: structuring and polishing the README of this project.

## Blocking cases handled

- **Deadlock prevention — breaking Coffman's conditions**

| Coffman condition | Status in Codexion |
|-------------------|--------------------|
| Mutual exclusion | **Inevitable** — a dongle is a single-user resource. Kept: that's the point of the exercise. |
| Hold and wait | **Eliminated by all-or-nothing acquisition** — A coder takes both dongles inside one critical section, or takes neither. A blocked coder always holds *zero* dongles. |
| No preemption | **Neutralized** — no dongle is ever forcibly taken, but every wait is bounded: at the missed burnout deadline the monitor stops the simulation and wakes all waiters. |
| Circular wait | **Impossible** — A cycle in the wait-for graph requires every coder in the cycle to *hold* a dongle while waiting for the next. Since waiters hold nothing, no cycle can ever form. |

Because deadlock requires all four conditions at once, eliminating hold-and-wait
(and making circular wait structurally impossible) is sufficient: the simulation
is deadlock-free by construction.
- **Starvation prevention:** each dongle's 2-slot wait queue is reordered on every push
  according to the chosen `scheduler` — `fifo` orders by request arrival time, `edf`
  orders by earliest burnout deadline (`last_compile_start + time_to_burnout`) — so the
  coder closest to burning out (or the one that has waited longest) is always served
  first among its two possible contenders. To make that first ordering meaningful,
  coders with an even id sleep 1 ms before entering their loop, staggering the initial
  burst of simultaneous requests at t = 0 so the very first scheduling decision reflects
  the chosen policy instead of arbitrary thread-scheduling order. This is a startup
  fairness measure, not a deadlock safeguard: deadlock is already ruled out structurally
  (see below), since a coder never holds one dongle while waiting on the other.
- **Cooldown handling:** releasing a dongle marks it as cooling and spawns a short-lived
  thread that sleeps `dongle_cooldown` ms before clearing the cooling flag and waking
  waiting coders. A dongle is never handed out again while its cooldown thread is still
  running, even though it is otherwise marked "usable" for state purposes.
- **Precise burnout detection:** a separate monitor thread polls every millisecond and
  compares each coder's last compile start time plus `time_to_burnout` against the
  current time, so a burnout is detected and logged within roughly 1 ms of the actual
  deadline — well inside the required 10 ms tolerance.
- **Log serialization:** every log line is produced through a single helper that takes
  the timestamp and calls `printf` while holding a dedicated logging mutex, so two
  threads can never interleave their output on the same line.

## Thread synchronization mechanisms

- **`general_lock` + `general_cond`** protect all shared dongle state (availability,
  cooldown flag, per-dongle wait queues) and coordinate coders waiting to compile. A
  coder calls `pthread_cond_wait` in a loop that re-checks its wait condition
  (priority on both dongles *and* both dongles available) on every wakeup, which guards
  against spurious wakeups and against races where two coders might otherwise both
  believe a dongle is free.
- **`action_lock`** is a separate mutex protecting the pairing of "read current
  timestamp" and "print it," so log lines are atomic and never interleave. It also
  guards the coder fields (`compiled_at`, `compilation_done`) that are written by the
  coder's own thread and read by the monitor thread, giving a safe, race-free handoff
  of that state between the two.
- **`stop_lock`** is a small, cheap mutex dedicated to the global stop flag, so any
  thread (coders, the sleep helper, the monitor) can poll `is_stop()` frequently without
  contending on `general_lock`.
- **Per-dongle cooldown threads:** instead of blocking the coder thread itself during a
  dongle's cooldown, each dongle release spawns a short-lived thread that sleeps for
  `dongle_cooldown` ms, then reacquires `general_lock`, clears the cooling flag, and
  broadcasts `general_cond`. The coder that eventually reclaims that dongle joins this
  thread first, guaranteeing the cooldown has fully elapsed before reuse.
- **Race condition example:** without `general_lock` wrapping the "check availability,
  then take" sequence, two coders could both observe an available dongle and both take
  it. Because the whole check-wait-take sequence happens under one mutex (and only the
  coder at index 0 of both relevant queues is ever considered a priority candidate),
  only one coder can ever win a given dongle at a time.
- **Coder ↔ monitor communication:** coders don't signal the monitor directly; instead
  the monitor polls each coder's shared, mutex-protected `compiled_at` /
  `compilation_done` fields once per millisecond. When it detects a burnout it sets the
  stop flag and broadcasts `general_cond`, which wakes every coder blocked on
  `general_lock`/`general_cond` so they can exit their loop cleanly.