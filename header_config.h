/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_config.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 13:06:17 by varandri          #+#    #+#             */
/*   Updated: 2026/07/28 14:56:05 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

typedef struct s_config
{
	int		coders_count;
	int		burnout_time;
	int		compile_time;
	int		debug_time;
	int		refactor_time;
	int		compile_required;
	int		dongle_cool_down;
	char	*scheduler;
}		t_config;

t_config	*new_config(void);
void		set_config(t_config *config, int *arg_conf, char *scheduler);
int			*parse_config(int argc, char **argv, char **scheduler);
