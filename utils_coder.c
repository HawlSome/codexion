/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_coder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 10:05:03 by varandri          #+#    #+#             */
/*   Updated: 2026/07/28 11:07:50 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_coder.h"

t_dongle *new_dongle(int cool_down)
{
	t_dongle	*dongle;

	dongle = (t_dongle *)malloc(sizeof(t_dongle));
	dongle->cool_down = cool_down;
	if (!dongle)
		return (NULL);
	return (dongle);
}

t_coder	*new_coder(int number)
{
	t_coder		*coder;
	coder = (t_coder*)malloc(sizeof(t_coder));
	coder->thread = NULL;
	coder->number = number;
	return (coder);
}

int	get_dongle(t_coder *coder)
{
	if (!coder)
		return (0);
	return (0);
}