/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_queue_sorting.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 17:04:49 by varandri          #+#    #+#             */
/*   Updated: 2026/08/23 18:32:57 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_codexion.h"

static void	swap(void *elem_1, void *elem_2)
{
	void *temp;

	if (!elem_1 || !elem_2)
		return ;
	temp = elem_1;
	elem_1 = elem_2;
	elem_2 = temp;
}	

void	edf_sort(t_heap_queue *queue, t_config *conf)
{
	t_coder *coder_1;
	t_coder *coder_2;

	coder_1 = (queue->coders)[0];
	coder_2 = (queue->coders)[1];
	if (get_elapsed_deadline(&coder_1->last_compile, conf->burnout_time)
		> get_elapsed_deadline(&coder_1->last_compile, conf->burnout_time))
		swap((void *)coder_1, (void *)coder_2);
}

void	fifo_sort(t_heap_queue *queue)
{
	t_coder *coder_1;
	t_coder *coder_2;

	coder_1 = (queue->coders)[0];
	coder_2 = (queue->coders)[1];
	if (get_time_ms(&coder_1->wait_entry) > get_time_ms(&coder_2->wait_entry))
		swap((void *)coder_1, (void *)coder_2);
}
