/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dongle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/28 21:51:52 by varandri          #+#    #+#             */
/*   Updated: 2026/08/28 23:39:24 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_codexion.h"

int	is_priority(t_coder *coder)
{
	if (!coder || !coder->l_dongle || !coder->l_dongle->queue
		|| !coder->l_dongle->queue->coders || !coder->r_dongle
		|| !coder->r_dongle->queue || !coder->r_dongle->queue->coders)
		return (0);
	if (
		coder->l_dongle->queue->coders[0] == coder
		&& coder->r_dongle->queue->coders[0] == coder
	)
		return (1);
	else
		return (0);
}

int	is_donlges_available(t_coder *coder)
{
	if (!coder)
		return (0);
	if (coder->l_dongle->is_usable && coder->r_dongle->is_usable
		&& !coder->l_dongle->is_cooling && !coder->r_dongle->is_cooling)
		return (1);
	return (0);
}
