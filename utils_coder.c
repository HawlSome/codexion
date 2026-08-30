/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_coder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 00:02:31 by varandri          #+#    #+#             */
/*   Updated: 2026/08/30 02:14:07 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_codexion.h"

static t_coder	*last_coder(t_coder *coder)
{
	while (coder && coder->next)
		coder = coder->next;
	return (coder);
}

static t_dongle	*new_dongle(t_config *conf)
{
	t_dongle	*dongle;

	if (!conf)
		return (NULL);
	dongle = (t_dongle *)malloc(sizeof(t_dongle));
	if (!dongle)
		return (NULL);
	dongle->is_usable = 1;
	dongle->is_cooling = 0;
	dongle->has_cooled = 0;
	dongle->cool_down_time = conf->dongle_cool_down;
	dongle->queue = new_heap_q(2, 0);
	return (dongle);
}

static t_coder	*new_coder(int id)
{
	t_coder	*coder;

	coder = (t_coder *)malloc(sizeof(t_coder));
	if (!coder)
		return (NULL);
	coder->id = id;
	coder->compilation_done = 0;
	coder->next = NULL;
	return (coder);
}

void	init_coders(int numbers, t_coder **coders, t_config *conf)
{
	t_coder		*tail;
	t_dongle	*dongle;
	int			i;

	if (!conf)
		return ;
	i = 1;
	while (i <= numbers)
	{
		if (!*coders)
		{
			dongle = new_dongle(conf);
			*coders = new_coder(i);
			(*coders)->l_dongle = dongle;
			i ++;
			continue ;
		}
		dongle = new_dongle(conf);
		tail = last_coder(*coders);
		tail->r_dongle = dongle;
		tail->next = new_coder(i);
		(tail->next)->l_dongle = dongle;
		i ++;
	}
	(tail->next)->r_dongle = (*coders)->l_dongle;
}
