/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_coder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 00:02:31 by varandri          #+#    #+#             */
/*   Updated: 2026/08/21 12:56:09 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_codexion.h"

static t_coder	*last_coder(t_coder *coder)
{
	while (coder && coder->next)
		coder = coder->next;
	return (coder);
}

static t_dongle	*new_dongle(void)
{
	t_dongle	*dongle;

	dongle = (t_dongle *)malloc(sizeof(t_dongle));
	if (!dongle)
		return (NULL);
	dongle->cool_down_time = 0;
	dongle->is_used = 0;
	pthread_cond_init(&(dongle->cond), NULL);
	pthread_mutex_init(&(dongle->lock), NULL);
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
	coder->is_burnt_out = 0;
	pthread_mutex_init(&(coder->lock), NULL);
	coder->next = NULL;
	return (coder);
}

void	init_coders(int numbers, t_coder **coders)
{
	t_coder		*tail;
	t_dongle	*dongle;
	int			i;

	i = 1;
	while(i <= numbers)
	{
		if (!*coders)
		{
			dongle = new_dongle();
			*coders = new_coder(i);
			(*coders)->l_dongle = dongle;
			i ++;
			continue ;
		}
		dongle = new_dongle();
		tail = last_coder(*coders);
		tail->r_dongle = dongle;
		tail->next = new_coder(i);
		(tail->next)->l_dongle = dongle;
		i ++;
	}
	(tail->next)->r_dongle = (*coders)->l_dongle;
}
