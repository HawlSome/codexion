/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_coder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 10:05:03 by varandri          #+#    #+#             */
/*   Updated: 2026/08/19 20:53:52 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_coder.h"

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
	return (dongle);
}

static t_coder	*new_coder(int id)
{
	t_coder		*coder;

	coder = (t_coder *)malloc(sizeof(t_coder));
	if (!coder)
		return (NULL);
	coder->id = id;
	coder->required_compilation = 0;
	coder->compile_time = 0;
	coder->debug_time = 0;
	coder->refactor_time = 0;
	coder->burnout_time = 0;
	coder->is_burnt_out = 0;
	coder->next = NULL;
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
		tail->next = new_coder(i);
		(tail->next)->l_dongle = dongle;
		i++;
	}
	(tail->next)->r_dongle = (*coder)->l_dongle;
}
