/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_simulation_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/28 14:23:27 by varandri          #+#    #+#             */
/*   Updated: 2026/08/29 00:40:35 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_codexion.h"

void	fail_safe_cool_down(void *c_arg)
{
	t_arg	*arg;

	if (!c_arg)
		return (NULL);
	arg = (t_arg *)c_arg;
	pthread_mutex_lock(&arg->conf->general_lock);
	arg->dongle->is_cooling = 0;
	pthread_cond_broadcast(&arg->conf->general_cond);
	pthread_mutex_unlock(&arg->conf->general_lock);
	free(arg);
}

void	compile(t_coder *coder, t_config *conf)
{
	long	compile_start;

	if (!coder || !conf)
		return ;
	pthread_mutex_lock(&conf->general_lock);
	while (!(is_priority(coder) && is_donlges_available(coder)))
		pthread_cond_wait(&conf->general_cond, &conf->general_lock);
	take_dongles(coder, conf);
	pthread_mutex_unlock(&conf->general_lock);
	compile_start = print_action(coder, conf, "is compiling");
	coder->last_compile_start = compile_start;
	usleep(conf->compile_time);
	coder->compilation_done ++;
	release_dongle(coder);
}

void	debug(t_coder *coder, t_config *conf)
{
	if (!coder || !conf)
		return ;
	print_action(coder, conf, "is debugging");
	usleep(conf->debug_time);
}

void	refactor(t_coder *coder, t_config *conf)
{
	if (!coder || !conf)
		return ;
	print_action(coder, conf, "is refactoring");
	usleep(conf->refactor_time);
}
