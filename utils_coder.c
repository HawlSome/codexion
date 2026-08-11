/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_coder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 10:05:03 by varandri          #+#    #+#             */
/*   Updated: 2026/08/12 00:35:40 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_coder.h"

t_dongle	*new_dongle(int cool_down)
{
	t_dongle	*dongle;

	dongle = (t_dongle *)malloc(sizeof(t_dongle));
	if (!dongle)
		return (NULL);
	dongle->cool_down = cool_down;
	return (dongle);
}

t_coder	*new_coder(int number)
{
	t_coder		*coder;

	coder = (t_coder *)malloc(sizeof(t_coder));
	if (!coder)
		return (NULL);
	coder->number = number;
	coder->compile_time = 0;
	coder->debug_time = 0;
	coder->refactor_time = 0;
	coder->burnout_time = 0;
	coder->dongle = new_dongle(0);
	coder->prev_coder = NULL;
	coder->next_coder = NULL;
	coder->is_last = 1;
	return (coder);
}

t_coder	*last_coder(t_coder *coder)
{
	while (coder && coder->next_coder && !coder->is_last)
		coder = coder->next_coder;
	return (coder);
}

void	arrange_coders(t_coder *coder)
{
	t_coder	*first_coder;

	if (!coder)
		return ;
	first_coder = coder;
	first_coder->prev_coder = last_coder(coder);
	while (coder && !coder->is_last)
	{
		(coder->next_coder)->prev_coder = coder;
		coder = coder->next_coder;
	}
	coder->next_coder = first_coder;
}

t_coder	*create_coders(int numbers)
{
	t_coder		*coder;
	t_coder		*tail;
	int			i;

	i = 1;
	coder = NULL;
	while (i <= numbers)
	{
		if (!coder)
		{
			coder = new_coder(i);
			i++;
			continue ;
		}
		tail = last_coder(coder);
		tail->is_last = 0;
		tail->next_coder = new_coder(i);
		i++;
	}
	arrange_coders(coder);
	return (coder);
}
