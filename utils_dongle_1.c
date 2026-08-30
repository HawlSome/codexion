/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dongle_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/28 01:05:37 by varandri          #+#    #+#             */
/*   Updated: 2026/08/30 16:26:20 by varandri         ###   ########.fr       */
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
	}
}

void	*cool_down(void *c_arg)
{
	t_arg	*arg;

	if (!c_arg)
		return (NULL);
	arg = (t_arg *)c_arg;
	usleep(arg->dongle->cool_down_time * 1000);
	pthread_mutex_lock(&arg->conf->general_lock);
	arg->dongle->has_cooled = 1;
	arg->dongle->is_cooling = 0;
	pthread_cond_broadcast(&arg->conf->general_cond);
	pthread_mutex_unlock(&arg->conf->general_lock);
	free(arg);
	return (NULL);
}

void	request_dongles(t_coder *coder, t_config *conf)
{
	if (!coder || !conf || is_stop(conf))
		return ;
	coder->wait_entry = get_time(conf);
	pthread_mutex_lock(&conf->general_lock);
	heap_push(coder->l_dongle->queue, coder, conf);
	heap_push(coder->r_dongle->queue, coder, conf);
	pthread_cond_broadcast(&conf->general_cond);
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
	pthread_cond_broadcast(&conf->general_cond);
}

void	release_dongles(t_coder *coder, t_config *conf)
{
	t_arg	*r_arg;
	t_arg	*l_arg;
	int		l_cool_down;
	int		r_cool_down;

	if (!coder || !conf)
		return ;
	l_arg = new_arg(coder, coder->l_dongle, NULL, conf);
	r_arg = new_arg(coder, coder->r_dongle, NULL, conf);
	pthread_mutex_lock(&conf->general_lock);
	coder->l_dongle->is_usable = 1;
	coder->l_dongle->is_cooling = 1;
	coder->r_dongle->is_usable = 1;
	coder->r_dongle->is_cooling = 1;
	pthread_cond_broadcast(&conf->general_cond);
	pthread_mutex_unlock(&conf->general_lock);
	l_cool_down = pthread_create(&coder->l_dongle->thread, NULL,
			cool_down, (void *)l_arg);
	r_cool_down = pthread_create(&coder->r_dongle->thread, NULL,
			cool_down, (void *)r_arg);
	if (l_cool_down != 0)
		fail_safe_cool_down((void *)l_arg);
	if (r_cool_down != 0)
		fail_safe_cool_down((void *)r_arg);
}
