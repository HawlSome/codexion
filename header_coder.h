/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_coder.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 08:41:55 by varandri          #+#    #+#             */
/*   Updated: 2026/08/14 12:39:09 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_config.h"
#include <pthread.h>

typedef struct s_dongle
{
	pthread_mutex_t	mutex;
	int				cool_down;
}		t_dongle;

typedef struct s_coder
{
	pthread_t		thread;
	int				number;
	int				compile_time;
	int				debug_time;
	int				refactor_time;
	int				burnout_time;
	t_dongle		*dongle;
	struct s_coder	*prev_coder;
	struct s_coder	*next_coder;
	int				is_last;
}		t_coder;

t_coder	*create_coders(int numbers);
void	set_coders(t_coder *coders, t_config config);
