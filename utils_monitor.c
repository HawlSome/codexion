/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 00:02:37 by varandri          #+#    #+#             */
/*   Updated: 2026/08/23 10:09:24 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_codexion.h"

t_monitor	*init_monitor(t_coder	*coders, t_config *conf)
{
	t_monitor	*monitor;

	monitor = (t_monitor *)malloc(sizeof(t_monitor));
	if (!monitor)
		return (NULL);
	monitor->coders = coders;
	monitor->conf = conf;
	monitor->stop = 0;
	gettimeofday(&(monitor->now), NULL);
	pthread_mutex_init(&(monitor->lock), NULL);
}