/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_coder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 10:05:03 by varandri          #+#    #+#             */
/*   Updated: 2026/07/28 12:57:35 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_coder.h"

t_dongle	*new_dongle(int cool_down)
{
	t_dongle	*dongle;

	dongle = (t_dongle *)malloc(sizeof(t_dongle));
	dongle->cool_down = cool_down;
	if (!dongle)
		return (NULL);
	return (dongle);
}

t_coder	*new_coder(int number, int dongle_cool_down)
{
	t_coder		*coder;

	coder = (t_coder *)malloc(sizeof(t_coder));
	coder->thread = NULL;
	coder->number = number;
	coder->compile_time = 0;
	coder->debug_time = 0;
	coder->refactor_time = 0;
	coder->burnout_time = 0;
	coder->compile_required = 0;
	*(coder->dongle) = new_dongle(dongle_cool_down);
	coder->prev_coder = NULL;
	coder->next_coder = NULL;
	coder->is_last = 1;
	if (!coder)
		return (NULL);
	return (coder);
}

t_coder	*last_coder(t_coder *coder)
{
	while (coder && !coder->is_last)
		coder = coder->next_coder;
	retun(coder);
}

t_coder	*create_coders(int numbers, int dongle_cood_down)
{
	t_coder		*coder;
	int			i;

	i = 1;
	coder = NULL;
	while (i <= numbers)
	{
		if (!coder)
		{
			coder = new_coder(i, dongle_cood_down);
			i++;
			continue ;
		}
		last_coder(coder)->next_coder = new_coder(i, dongle_cood_down);
		(last_coder(coder)->next_coder)->prev_coder = last_coder(coder);
		last_coder(coder)->is_last = 0;
		i++;
	}
	last_coder(coder)->next_coder = coder;
	coder->prev_coder = last_coder(coder);
	return (coder);
}
