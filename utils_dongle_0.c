/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dongle_0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/28 21:51:52 by varandri          #+#    #+#             */
/*   Updated: 2026/09/01 21:49:03 by varandri         ###   ########.fr       */
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

void	fail_safe_cool_down(void *c_arg)
{
	t_arg	*arg;

	if (!c_arg)
		return ;
	arg = (t_arg *)c_arg;
	pthread_mutex_lock(&arg->conf->general_lock);
	arg->dongle->is_cooling = 0;
	pthread_cond_broadcast(&arg->conf->general_cond);
	pthread_mutex_unlock(&arg->conf->general_lock);
	free(arg);
}

void	*cool_down(void *c_arg)
{
	t_arg	*arg;

	if (!c_arg)
		return (NULL);
	arg = (t_arg *)c_arg;
	msleep(arg->conf, arg->dongle->cool_down_time);
	pthread_mutex_lock(&arg->conf->general_lock);
	arg->dongle->has_cooled = 1;
	arg->dongle->is_cooling = 0;
	pthread_cond_broadcast(&arg->conf->general_cond);
	pthread_mutex_unlock(&arg->conf->general_lock);
	free(arg);
	return (NULL);
}

void	init_cooldown(t_coder *coder, t_config *conf)
{
	t_arg	*r_arg;
	t_arg	*l_arg;
	int		l_cool_down;
	int		r_cool_down;

	l_arg = new_arg(coder, coder->l_dongle, NULL, conf);
	r_arg = new_arg(coder, coder->r_dongle, NULL, conf);
	l_cool_down = pthread_create(&coder->l_dongle->thread, NULL,
			cool_down, (void *)l_arg);
	r_cool_down = pthread_create(&coder->r_dongle->thread, NULL,
			cool_down, (void *)r_arg);
	if (!l_cool_down)
		coder->l_dongle->thread_created = 1;
	if (!r_cool_down)
		coder->r_dongle->thread_created = 1;
	if (l_cool_down != 0)
		fail_safe_cool_down((void *)l_arg);
	if (r_cool_down != 0)
		fail_safe_cool_down((void *)r_arg);
}
