/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_coder.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 08:41:55 by varandri          #+#    #+#             */
/*   Updated: 2026/08/19 20:52:40 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_CODER_H
# define HEADER_CODER_H
# include "header_config.h"

typedef struct s_dongle
{
	pthread_mutex_t	mutex;
	int				is_used;
	int				cool_down_time;
}		t_dongle;

typedef struct s_coder
{
	pthread_t		thread;
	int				id;
	int				required_compilation;
	int				compile_time;
	int				debug_time;
	int				refactor_time;
	int				burnout_time;
	int				is_burnt_out;
	t_dongle		*l_dongle;
	t_dongle		*r_dongle;
	struct s_coder	*next;
}		t_coder;

void	create_coders(int numbers, t_coder	**coder);
void	set_coders(t_coder *coders, t_config *config);
#endif
