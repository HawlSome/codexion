/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_simulation_0.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/28 14:23:27 by varandri          #+#    #+#             */
/*   Updated: 2026/08/30 21:18:21 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_codexion.h"

static void	compile(t_coder *coder, t_config *conf)
{
	long	compile_start;

	if (!coder || !conf)
		return ;
	pthread_mutex_lock(&conf->general_lock);
	while (!is_stop(conf)
		&& !(is_priority(coder) && is_donlges_available(coder)))
		pthread_cond_wait(&conf->general_cond, &conf->general_lock);
	if (is_stop(conf))
	{
		pthread_mutex_unlock(&conf->general_lock);
		return ;
	}
	take_dongles(coder, conf);
	pthread_mutex_unlock(&conf->general_lock);
	compile_start = print_action(coder, conf, "is compiling");
	pthread_mutex_lock(&conf->action_lock);
	coder->last_compile_start = compile_start;
	pthread_mutex_unlock(&conf->action_lock);
	usleep(conf->compile_time * 1000);
	pthread_mutex_lock(&conf->action_lock);
	coder->compilation_done++;
	pthread_mutex_unlock(&conf->action_lock);
	release_dongles(coder, conf);
}

static void	debug(t_coder *coder, t_config *conf)
{
	if (!coder || !conf || is_stop(conf))
		return ;
	print_action(coder, conf, "is debugging");
	usleep(conf->debug_time * 1000);
}

static void	refactor(t_coder *coder, t_config *conf)
{
	if (!coder || !conf || is_stop(conf))
		return ;
	print_action(coder, conf, "is refactoring");
	usleep(conf->refactor_time * 1000);
}

void	*routine(void *r_arg)
{
	t_arg	*arg;

	if (!r_arg)
		return (NULL);
	arg = (t_arg *)r_arg;
	if (arg->coder->id % 2 == 0)
		usleep(1000);
	while (!is_stop(arg->conf)
		&& arg->coder->compilation_done < arg->conf->compile_required)
	{
		request_dongles(arg->coder, arg->conf);
		compile(arg->coder, arg->conf);
		debug(arg->coder, arg->conf);
		refactor(arg->coder, arg->conf);
	}
	free(arg);
	return (NULL);
}

void	start_coders_routines(t_coder *coders, t_config *conf)
{
	t_arg	*r_arg;
	t_coder	*coder;

	if (!coders || !conf)
		return ;
	coder = coders;
	while (coder)
	{
		r_arg = new_arg(coder, NULL, NULL, conf);
		if (pthread_create(&coder->thread, NULL, routine, r_arg) != 0)
		{
			free(r_arg);
			return ;
		}
		coder = coder->next;
	}
}
