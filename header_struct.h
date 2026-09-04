/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 19:56:21 by varandri          #+#    #+#             */
/*   Updated: 2026/09/04 17:31:55 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_STRUCT_H
# define HEADER_STRUCT_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_dongle	t_dongle;

typedef struct s_config
{
	struct timeval	t_0;
	pthread_mutex_t	general_lock;
	pthread_mutex_t	stop_lock;
	pthread_mutex_t	action_lock;
	pthread_cond_t	general_cond;
	long			stop;
	long			coders_count;
	long			burnout_time;
	long			compile_time;
	long			debug_time;
	long			refactor_time;
	long			compile_required;
	long			dongle_cool_down;
	long			compilation_done;
	char			*scheduler;
}		t_config;

typedef struct s_coder
{
	pthread_t		thread;
	int				id;
	long			compilation_done;
	t_dongle		*l_dongle;
	t_dongle		*r_dongle;
	long			compiled_at;
	long			wait_entry;
	struct s_coder	*next;
}		t_coder;

typedef struct s_heap_queue
{
	t_coder	**coders;
	int		size;
	int		capacity;
}		t_heap_queue;

typedef struct s_dongle
{
	pthread_t		thread;
	int				thread_created;
	int				is_usable;
	int				is_cooling;
	int				has_cooled;
	t_heap_queue	*queue;
}		t_dongle;

typedef struct s_arg
{
	t_coder		*coder;
	t_dongle	*dongle;
	t_coder		*coders;
	t_config	*conf;
}		t_arg;

#endif
