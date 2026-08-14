/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_coder_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 11:42:36 by varandri          #+#    #+#             */
/*   Updated: 2026/08/14 12:59:27 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_coder.h"
#include "header_config.h"

void	set_coders(t_coder *coders, t_config *config)
{
	int	i;

	while (i < config->coders_count)
	{
		coders->burnout_time = config->burnout_time;
		coders->compile_time = config->compile_time;
		coders->debug_time = config->debug_time;
		coders->refactor_time = config->refactor_time;
		coders = coders->next_coder;
	}
}
