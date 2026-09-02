/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_simulation_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 15:13:35 by varandri          #+#    #+#             */
/*   Updated: 2026/09/03 00:29:34 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_codexion.h"

int	should_continue(t_coder *coder, t_config *conf)
{
	int	should;

	if (!coder || !conf)
		return (0);
	pthread_mutex_lock(&conf->action_lock);
	should = (coder->compilation_done != conf->compile_required);
	pthread_mutex_unlock(&conf->action_lock);
	return (should);
}

void	end_coders_routines(t_coder *coder)
{
	while (coder)
	{
		pthread_join(coder->thread, NULL);
		coder = coder->next;
	}
}
