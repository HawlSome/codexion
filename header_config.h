/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_config.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 13:06:17 by varandri          #+#    #+#             */
/*   Updated: 2026/08/14 12:31:34 by varandri         ###   ########.fr       */
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

void	create_config(int argc, char **argv, t_config **config);
