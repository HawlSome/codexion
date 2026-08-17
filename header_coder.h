/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_coder.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 08:41:55 by varandri          #+#    #+#             */
/*   Updated: 2026/08/17 13:13:37 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_CODER_H
# define HEADER_CODER_H
# include "header_config.h"

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
	struct s_coder	*prev;
	struct s_coder	*next;
	int				is_last;
}		t_coder;

void	create_coders(int numbers, t_coder	**coder);
void	set_coders(t_coder *coders, t_config *config);
#endif