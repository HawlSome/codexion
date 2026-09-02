*This project has been created as part of the 42 curriculum by varandri*.

# Codexion

> Master the race for resources before the deadline masters you.

**Codexion** is a concurrency simulation in C: several coders share a co-working hub
with a single Quantum Compiler and a limited pool of USB dongles. Each coder needs
**two dongles at once** to compile, and everyone must compile regularly or they
**burn out**. All coordination happens through POSIX threads, mutexes, condition
variables and custom priority queues, under one of two arbitration policies:
`fifo` or `edf` (Earliest Deadline First).

Think *Dining Philosophers* — except the philosophers are coders, the forks are USB
dongles, and starvation is measured in milliseconds.

## Description

- One or more coders sit in a circular, inclusive co-working hub; in the center
  stands a shared **Quantum Compiler**. Coder 1 sits next to coder *N*.
- Coders cycle through three exclusive activities: **compile → debug → refactor** —
  never two at once — then immediately compete for dongles again.
- There are as many **USB dongles** as coders, one between each pair of neighbors.
  A lone coder shares the table with a single dongle that serves both hands.
- Compiling requires **two dongles simultaneously, one in each hand**.
- After release, a dongle enters a **cooldown** for `dongle_cooldown` ms and cannot
  be taken by anyone.
- If a coder does not **start** compiling within `time_to_burnout` ms of their last
  compile start (or of the simulation start), they **burn out**.
- The simulation stops on burnout, or successfully once **every** coder has compiled
  at least `number_of_compiles_required` times.
- Coders never communicate with each other and never read another coder's deadline:
  the only shared channel is the dongles themselves.

### Scheduling policies

When several coders wait for the same dongle, the dongle is granted according to
the `scheduler` argument:

| Scheduler | Arbitration |
|-----------|-------------|
| `fifo` | First In, First Out — earliest request (`wait_entry` timestamp) wins |
| `edf` | Earliest Deadline First — closest burnout deadline (`compiled_at + time_to_burnout`) wins, ties broken by arrival order |

## Instructions

### Compilation

Requires a Unix-like system with POSIX threads, `cc` and `make`.

```bash
make        # build codexion
make clean  # remove object files
make fclean # remove objects and the binary
make re     # fclean + all
```

Sources live in `coders/`. Compiled with `-Wall -Wextra -Werror -pthread`.
No external libraries (libft not used).

### Usage

```bash
./codexion number_of_coders time_to_burnout time_to_compile time_to_debug \
           time_to_refactor number_of_compiles_required dongle_cooldown scheduler
```

All eight arguments are mandatory:

| Argument | Unit | Meaning |
|----------|------|---------|
| `number_of_coders` | — | Number of coders (and of dongles); must be ≥ 1 |
| `time_to_burnout` | ms | Max time without *starting* a compile before burnout |
| `time_to_compile` | ms | Compile duration — both dongles held the whole time |
| `time_to_debug` | ms | Debug duration |
| `time_to_refactor` | ms | Refactor duration; then the coder immediately competes again |
| `number_of_compiles_required` | — | Per-coder compile quota that ends the simulation |
| `dongle_cooldown` | ms | Time after release during which a dongle cannot be taken |
| `scheduler` | — | Exactly `fifo` or `edf` |

Invalid input — wrong argument count, non-integers, negative values, zero coders,
or a scheduler other than `fifo`/`edf` — is rejected with an error message.

### Example

```bash
./codexion 4 800 200 200 200 7 200 fifo
```

Every state change is logged as `timestamp_in_ms X <state>`:

```
0 1 has taken a dongle
2 1 has taken a dongle
2 1 is compiling
202 1 is debugging
402 1 is refactoring
405 2 has taken a dongle
406 2 has taken a dongle
406 2 is compiling
...
1505 4 burned out
```
## Implementation overview

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

## Blocking cases handled

### Deadlock prevention — breaking Coffman's conditions

| Coffman condition | Status in Codexion |
|-------------------|--------------------|
| Mutual exclusion | Inherent — a dongle is a single-user resource. Kept: that's the point of the exercise. |
| Hold and wait | **Eliminated by all-or-nothing acquisition.** A coder takes both dongles inside one critical section, or takes neither. A blocked coder always holds *zero* dongles. |
| No preemption | Neutralized — no dongle is ever forcibly taken, but every wait is bounded: at the missed burnout deadline the monitor stops the simulation and wakes all waiters. |
| Circular wait | **Impossible.** A cycle in the wait-for graph requires every coder in the cycle to *hold* a dongle while waiting for the next. Since waiters hold nothing, no cycle can ever form. |

Because deadlock requires all four conditions at once, eliminating hold-and-wait
(and making circular wait structurally impossible) is sufficient: the simulation
is deadlock-free by construction.

### Starvation prevention (liveness)

- **`fifo`**: queue positions are fixed at request time by the `wait_entry`
  timestamp. The coder with the globally earliest `wait_entry` is necessarily at
  the head of *both* its queues — anyone ahead of it in either queue would have
  had to request even earlier, a contradiction. The earliest waiter is therefore
  always grantable as soon as its dongles are free: nobody is overtaken forever.
- **`edf`**: a waiting coder's deadline (`compiled_at + time_to_burnout`)
  is **frozen** while it waits, whereas every competitor that compiles again
  pushes its own deadline further away. The longer a coder waits, the more urgent
  its deadline becomes relative to the field — it eventually owns the earliest
  deadline, sits at the head of both queues, and is served. Ties break by arrival
  order. Provided the parameters are feasible, no coder starves.

### Cooldown handling

Releasing a dongle atomically marks it `is_cooling` and spawns a timer thread
that sleeps exactly `dongle_cooldown` ms, then clears the flag and broadcasts.
Acquisition requires `!is_cooling`, so a cooling dongle can never be taken — and
because the flag and the acquisition check live under the same `general_lock`,
"cooldown expires" and "coder takes the dongle" can never interleave. The
`pthread_create` failure path is covered too: the cooldown is lifted immediately
so the dongle can never get stuck.

### Precise burnout detection

A dedicated **monitor thread** owns burnout detection — the coders themselves
never check deadlines:

1. Every 1 ms, it scans all coders, reading `compiled_at` and
   `compilation_done` under `action_lock` (no torn reads).
2. Deadline = `compiled_at + time_to_burnout`, initialized to the
   simulation start for every coder.
3. On expiry it calls `set_stop()` (stop flag + broadcast, waking every waiter)
   and prints `X burned out`.

A 1 ms poll plus the broadcast wake means the message appears within ~1–2 ms of
the event — comfortably inside the required 10 ms window. Two correctness
details: `compiled_at` is written at the *instant* the dongles are
acquired (a coder that just started compiling can never be falsely reported),
and coders that already reached `compile_required` are exempt (they finished,
they didn't burn out).

### Log serialization

`print_action()` takes `action_lock` around the timestamp capture **and** the
`printf`: the whole line — timestamp included — is emitted as one atomic unit.
Two threads can never interleave on a line, and because the timestamp is taken
under the lock, log timestamps are monotonic by construction.

## Thread synchronization mechanisms

| Primitive | Guards |
|-----------|--------|
| `pthread_mutex_t general_lock` + `pthread_cond_t general_cond` | All dongle state (`is_usable`, `is_cooling`), every priority queue, and the acquisition protocol; coders block on the cond var |
| `pthread_mutex_t stop_lock` | The `stop` flag (read constantly via `is_stop()`) |
| `pthread_mutex_t action_lock` | Coder vitals (`compiled_at`, `compilation_done`) shared with the log output |

**Lock hierarchy:** `general_lock` → `action_lock`, and `stop_lock` is a leaf
(never held while acquiring another lock). The order is never reversed, so the
locks themselves cannot deadlock.

### Event pattern (custom event)

`general_cond` acts as a small event bus: every relevant change — new request,
dongle release, cooldown expiry, stop — **broadcasts** on it, and every waiter
re-checks its own predicate in a `while` loop (which also makes spurious
wakeups harmless). `set_stop()` is the terminal event: it sets the flag under
`stop_lock`, then broadcasts so all blocked coders exit promptly. This replaces
busy-waiting with pure blocking waits and gives every thread a race-free
shutdown path.

### The priority queue (heap)

C89 ships no priority queue, so each dongle owns a **binary min-heap** of
pending requests (`heap_push` / `heap_pop`). The comparison key
depends on the scheduler: `wait_entry` for `fifo`, the burnout deadline for
`edf` (with `wait_entry` as tie-breaker).

### Race prevented: two coders, one dongle

Without protection, two coders can observe the same free dongle at the same
instant and both "take" it — duplicating the resource. In Codexion, the entire
check-and-claim sequence is atomic under `general_lock`:

```c
pthread_mutex_lock(&conf->general_lock);
while (!is_stop(conf)
	&& !(is_priority(coder) && is_donlges_available(coder)))
	pthread_cond_wait(&conf->general_cond, &conf->general_lock);
take_dongles(coder, conf);   /* both dongles, or none */
pthread_mutex_unlock(&conf->general_lock);
```

A coder is granted dongles only if it is **head of both its queues** *and*
**both dongles are free and off cooldown** — checked and claimed inside a single
critical section. Exactly one coder can win; the others go back to sleep.

### Race prevented: coder ⇄ monitor communication

The coder publishes its new state the moment it acquires the dongles; the
monitor reads it under the same lock one millisecond later — never a stale or
half-written value:

```c
/* coder thread, immediately after acquiring both dongles: */
pthread_mutex_lock(&conf->action_lock);
coder->compiled_at = get_time(conf);
coder->compilation_done++;
pthread_mutex_unlock(&conf->action_lock);

/* monitor thread, under the same lock: */
burnt_out = (coder->compilation_done < conf->compile_required
		&& get_time(conf) >= coder->compiled_at
		+ conf->burnout_time);
```

Note what is *not* shared: coders never read each other's deadlines or compile
counts. The only shared channel between coders is dongle state — the monitor is
the sole global observer, exactly as the scenario demands.

## Project structure

```
codexion/
└──README.md
└──coders/
    ├── Makefile
    ├── header_codexion.h     # shared types, structs, prototypes
    ├── main.c                # entry point, orchestration, teardown
    ├── helpers.c             # ft_atol, timing, logging
    ├── utils_config.c        # argument parsing and validation
    ├── utils_coder.c         # coder/dongle creation, ring construction
    ├── utils_dongle_0.c      # queue priority checks, cooldown threads
    ├── utils_dongle_1.c      # acquisition protocol: request/take/release
    ├── utils_queue_0.c       # heap ordering keys (fifo / edf)
    ├── utils_queue_1.c       # binary min-heap (push / pop)
    ├── utils_monitor.c       # burnout detection, stop mechanism
    ├── utils_simulation_0.c  # coder routine: compile/debug/refactor loop
    ├── utils_simulation_1.c  # coder thread lifecycle (join)
    ├── utils_cleaner.c       # full cleanup: threads, mutexes, memory
    └── verifier.c            # post-init structural sanity checks
```

## Resources
- POSIX man pages: `pthread_create(3)`, `pthread_mutex_lock(3)`,
  `pthread_cond_wait(3)`, `pthread_cond_broadcast(3)`, `gettimeofday(2)`,
  `usleep(3)`
- [GeerksForGeek](https://www.geeksforgeeks.org/c/multithreading-in-c/): `Practical Documentation`
	and `examples of the usage of threads` followed by `brief explanations`.
- [Youtube](https://www.youtube.com/watch?v=uA8X5zNOGw8&list=PL9IEJIKnBJjFZxuqyJ9JqVYmuFZHr7CFM): `Series of tutorial` about threads in C POSIX.

#### AI usage

<!-- Personalize this list so it honestly reflects YOUR workflow. -->

- **Concept explanations**: How threads work, how they share the same data, and how to manipulate those
  safely.
- **Documentation**: polishing the structure and English of this README; every
  technical claim describes code I wrote and can defend.
