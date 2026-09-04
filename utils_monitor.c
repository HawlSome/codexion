/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 00:02:37 by varandri          #+#    #+#             */
/*   Updated: 2026/09/04 15:38:50 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_codexion.h"

static int	is_burnt_out(t_coder *coder, t_config *conf)
{
	int	burnt_out;

	if (!coder || !conf)
		return (1);
	pthread_mutex_lock(&conf->action_lock);
	burnt_out = (coder->compilation_done < conf->compile_required
			&& (get_time(conf)
				>= coder->compiled_at + conf->burnout_time));
	pthread_mutex_unlock(&conf->action_lock);
	return (burnt_out);
}

void	set_stop(t_config *conf)
{
	if (!conf)
		return ;
	pthread_mutex_lock(&conf->general_lock);
	pthread_mutex_lock(&conf->stop_lock);
	conf->stop = 1;
	pthread_mutex_unlock(&conf->stop_lock);
	pthread_cond_broadcast(&conf->general_cond);
	pthread_mutex_unlock(&conf->general_lock);
}

int	is_stop(t_config *conf)
{
	int	stopped;

	if (!conf)
		return (1);
	pthread_mutex_lock(&conf->stop_lock);
	stopped = conf->stop;
	pthread_mutex_unlock(&conf->stop_lock);
	return (stopped);
}

void	*monitoring(void *m_arg)
{
	t_arg	*arg;
	t_coder	*coder;

	if (!m_arg)
		return (NULL);
	arg = (t_arg *)m_arg;
	while (!is_stop(arg->conf))
	{
		coder = arg->coders;
		while (coder)
		{
			if (is_burnt_out(coder, arg->conf))
			{
				set_stop(arg->conf);
				print_action(coder, arg->conf, "burned out");
				break ;
			}
			coder = coder->next;
		}
		usleep(1000);
	}
	free(arg);
	return (NULL);
}

void	start_monitoring(pthread_t *monitor, t_config *conf, t_coder *coders)
{
	t_arg	*m_arg;

	if (!monitor || !conf || !coders)
		return ;
	m_arg = new_arg(NULL, NULL, coders, conf);
	if (pthread_create(monitor, NULL, monitoring, (void *)m_arg) != 0)
		return ;
}
