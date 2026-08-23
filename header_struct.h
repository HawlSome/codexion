/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 19:56:21 by varandri          #+#    #+#             */
/*   Updated: 2026/08/23 17:26:45 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_STRUCT_H
# define HEADER_STRUCT_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_dongle	t_dongle;

typedef struct s_config
{
	int				coders_count;
	int				burnout_time;
	int				compile_time;
	int				debug_time;
	int				refactor_time;
	int				compile_required;
	int				dongle_cool_down;
	char			*scheduler;
}		t_config;

typedef struct s_coder
{
	pthread_t		thread;
	pthread_mutex_t	lock;
	int				id;
	int				compilation_done;
	int				is_burnt_out;
	t_dongle		*l_dongle;
	t_dongle		*r_dongle;
	struct timeval	last_compile;
	struct timeval	wait_entry;
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
	pthread_mutex_t	lock;
	pthread_cond_t	cond;
	int				is_used;
	int				cool_down_time;
	t_heap_queue	*queue;
}		t_dongle;

typedef struct s_monitor
{
	pthread_t		thread;
	pthread_mutex_t	lock;
	int				stop;
	struct timeval	now;
	t_coder			*coders;
	t_config		*conf;
}		t_monitor;

typedef struct s_arg
{
	t_coder		*coder;
	t_monitor	*monitor;
}		t_arg;

#endif
