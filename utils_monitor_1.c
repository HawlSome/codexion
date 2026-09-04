/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_monitor_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 12:20:52 by varandri          #+#    #+#             */
/*   Updated: 2026/09/04 12:35:25 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_codexion.h"

int	simulation_stop(t_config *conf)
{
	int	compilation_done;

	pthread_mutex_lock(&conf->action_lock);
	compilation_done = conf->compilation_done;
	pthread_mutex_unlock(&conf->action_lock);
	if (conf->compile_required * conf->coders_count <= compilation_done)
	{
		set_stop(conf);
		return (1);
	}
	return (0);
}
