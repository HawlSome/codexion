/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_coder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 10:05:03 by varandri          #+#    #+#             */
/*   Updated: 2026/08/17 14:29:56 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_coder.h"

static t_coder	*last_coder(t_coder *coder)
{
	while (coder && coder->next && !coder->is_last)
		coder = coder->next;
	return (coder);
}

static void	arrange_coders(t_coder *coder)
{
	t_coder	*first_coder;

	if (!coder)
		return ;
	first_coder = coder;
	first_coder->prev = last_coder(coder);
	while (coder && !coder->is_last)
	{
		(coder->next)->prev = coder;
		coder = coder->next;
	}
	coder->next = first_coder;
}

static t_dongle	*new_dongle(int cool_down, int is_used)
{
	t_dongle	*dongle;

	dongle = (t_dongle *)malloc(sizeof(t_dongle));
	if (!dongle)
		return (NULL);
	dongle->cool_down = cool_down;
	dongle->is_used = is_used;
	return (dongle);
}

static t_coder	*new_coder(int number)
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
	coder->dongle = new_dongle(0, 0);
	coder->prev = NULL;
	coder->next = NULL;
	coder->is_last = 1;
	return (coder);
}

void	create_coders(int numbers, t_coder	**coder)
{
	t_coder		*tail;
	int			i;

	i = 1;
	while (i <= numbers)
	{
		if (!*coder)
		{
			*coder = new_coder(i);
			i++;
			continue ;
		}
		tail = last_coder(*coder);
		tail->is_last = 0;
		tail->next = new_coder(i);
		i++;
	}
	arrange_coders(*coder);
}
