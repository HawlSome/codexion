/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_queue_sorting.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 17:04:49 by varandri          #+#    #+#             */
/*   Updated: 2026/08/24 09:40:37 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_codexion.h"

static void	swap(t_coder **coders)
{
	void	*temp;

	if (!coders || !*coders)
		return ;
	temp = *coders;
	coders[0] = coders[1];
	coders[1] = temp;
}

void	edf_sort(t_heap_queue *queue, t_config *conf)
{
	t_coder	*coder_1;
	t_coder	*coder_2;

	coder_1 = (queue->coders)[0];
	coder_2 = (queue->coders)[1];
	if (get_elapsed_deadline(&coder_1->last_compile, conf->burnout_time)
		> get_elapsed_deadline(&coder_1->last_compile, conf->burnout_time))
		swap(queue->coders);
}

void	fifo_sort(t_heap_queue *queue)
{
	t_coder	*coder_1;
	t_coder	*coder_2;

	coder_1 = (queue->coders)[0];
	coder_2 = (queue->coders)[1];
	if (get_time_ms(&coder_1->wait_entry) > get_time_ms(&coder_2->wait_entry))
		swap(queue->coders);
}
