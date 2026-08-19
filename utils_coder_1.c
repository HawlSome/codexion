/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_coder_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 11:42:36 by varandri          #+#    #+#             */
/*   Updated: 2026/08/19 20:53:09 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_coder.h"
#include "header_config.h"

void	set_coders(t_coder *coders, t_config *config)
{
	while (coders)
	{
		coders->required_compilation = config->compile_required;
		coders->burnout_time = config->burnout_time;
		coders->compile_time = config->compile_time;
		coders->debug_time = config->debug_time;
		coders->refactor_time = config->refactor_time;
		if (coders->l_dongle && coders->r_dongle)
		{
			(coders->l_dongle)->cool_down_time = config->dongle_cool_down;
			(coders->r_dongle)->cool_down_time = config->dongle_cool_down;
		}
		coders = coders->next;
	}
}
