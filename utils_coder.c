/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_coder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 10:05:03 by varandri          #+#    #+#             */
/*   Updated: 2026/08/17 21:55:23 by varandri         ###   ########.fr       */
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
	coder->r_dongle = first_coder->l_dongle;
}

static t_dongle	*new_dongle(void)
{
	t_dongle	*dongle;

	dongle = (t_dongle *)malloc(sizeof(t_dongle));
	if (!dongle)
		return (NULL);
	dongle->cool_down_time = 0;
	dongle->is_used = 0;
	return (dongle);
}

static t_coder	*new_coder(int id)
{
	t_coder		*coder;

	coder = (t_coder *)malloc(sizeof(t_coder));
	if (!coder)
		return (NULL);
	coder->id = id;
	coder->compile_time = 0;
	coder->debug_time = 0;
	coder->refactor_time = 0;
	coder->burnout_time = 0;
	coder->prev = NULL;
	coder->next = NULL;
	coder->is_last = 1;
	return (coder);
}

void	create_coders(int numbers, t_coder	**coder)
{
	t_coder		*tail;
	t_dongle	*dongle;
	int			i;

	i = 1;
	while (i <= numbers)
	{
		if (!*coder)
		{
			dongle = new_dongle();
			*coder = new_coder(i);
			(*coder)->l_dongle = dongle;
			i++;
			continue ;
		}
		dongle = new_dongle();
		tail = last_coder(*coder);
		tail->r_dongle = dongle;
		tail->is_last = 0;
		tail->next = new_coder(i);
		(tail->next)->l_dongle = dongle;
		i++;
	}
	arrange_coders(*coder);
}
