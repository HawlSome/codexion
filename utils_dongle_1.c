/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dongle_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/28 01:05:37 by varandri          #+#    #+#             */
/*   Updated: 2026/09/02 17:18:57 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_codexion.h"

void	join_cool_down(t_dongle *dongle)
{
	if (!dongle)
		return ;
	if (dongle->has_cooled)
	{
		pthread_join(dongle->thread, NULL);
		dongle->has_cooled = 0;
		dongle->thread_created = 0;
	}
}

void	request_dongles(t_coder *coder, t_config *conf)
{
	if (!coder || !conf || is_stop(conf))
		return ;
	coder->wait_entry = get_time(conf);
	pthread_mutex_lock(&conf->general_lock);
	if (coder->l_dongle)
		heap_push(coder->l_dongle->queue, coder, conf);
	if (coder->r_dongle)
		heap_push(coder->r_dongle->queue, coder, conf);
	pthread_mutex_unlock(&conf->general_lock);
}

void	take_dongles(t_coder *coder, t_config *conf)
{
	if (!coder || !conf)
		return ;
	print_action(coder, conf, "has taken a dongle");
	join_cool_down(coder->l_dongle);
	coder->l_dongle->is_usable = 0;
	heap_pop(coder->l_dongle->queue, coder);
	print_action(coder, conf, "has taken a dongle");
	join_cool_down(coder->r_dongle);
	coder->r_dongle->is_usable = 0;
	heap_pop(coder->r_dongle->queue, coder);
}

void	release_dongles(t_coder *coder, t_config *conf)
{
	if (!coder || !conf)
		return ;
	pthread_mutex_lock(&conf->general_lock);
	coder->l_dongle->is_usable = 1;
	coder->l_dongle->is_cooling = 1;
	coder->r_dongle->is_usable = 1;
	coder->r_dongle->is_cooling = 1;
	init_cooldown(coder, conf);
	pthread_mutex_unlock(&conf->general_lock);
}
