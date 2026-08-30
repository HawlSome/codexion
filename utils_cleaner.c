/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cleaner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 02:59:13 by varandri          #+#    #+#             */
/*   Updated: 2026/08/30 20:00:05 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_codexion.h"

static void	clean_queue(t_heap_queue *queue)
{
	if (!queue)
		return ;
	free(queue->coders);
	free(queue);
}

static void	clean_dongles(t_dongle *l_dongle)
{
	if (!l_dongle)
		return ;
	clean_queue(l_dongle->queue);
	if (l_dongle->thread_created)
		pthread_join(l_dongle->thread, NULL);
	free(l_dongle);
}

static void	clean_coder(t_coder *coder)
{
	t_coder	*curr;

	while (coder)
	{
		curr = coder;
		clean_dongles(coder->l_dongle);
		coder = coder->next;
		free(curr);
	}
}

static void	clean_conf(t_config *conf)
{
	if (!conf)
		return ;
	pthread_mutex_destroy(&conf->action_lock);
	pthread_mutex_destroy(&conf->general_lock);
	pthread_mutex_destroy(&conf->stop_lock);
	pthread_cond_destroy(&conf->general_cond);
	free(conf);
}

void	program_clean(t_coder *coder, t_config *conf)
{
	if (!coder || !conf)
		return ;
	clean_coder(coder);
	clean_conf(conf);
}
