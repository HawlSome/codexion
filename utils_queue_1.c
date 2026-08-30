/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_queue_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 00:02:39 by varandri          #+#    #+#             */
/*   Updated: 2026/08/30 14:10:43 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_codexion.h"

static t_coder	**create_tab_coders(int capacity)
{
	t_coder	**tab_coder;

	tab_coder = (t_coder **)malloc(capacity * sizeof(*tab_coder));
	if (!tab_coder)
		return (NULL);
	memset(tab_coder, 0, capacity * sizeof(t_coder *));
	return (tab_coder);
}

static void	sort_tab(t_heap_queue *queue, t_config *conf)
{
	if (!queue || !conf->scheduler || queue->size != queue->capacity
		|| !queue->coders)
		return ;
	if (!strcmp(conf->scheduler, "edf") || !strcmp(conf->scheduler, "EDF"))
		edf_sort(queue, conf);
	if (!strcmp(conf->scheduler, "fifo") || !strcmp(conf->scheduler, "FIFO"))
		fifo_sort(queue);
}

t_heap_queue	*new_heap_q(int capacity, int size)
{
	t_heap_queue	*heap_q;

	heap_q = (t_heap_queue *)malloc(sizeof(t_heap_queue));
	if (!heap_q)
		return (NULL);
	heap_q->capacity = capacity;
	heap_q->size = size;
	heap_q->coders = create_tab_coders(capacity);
	if (!heap_q->coders)
	{
		free(heap_q);
		heap_q = NULL;
	}
	return (heap_q);
}

void	heap_push(t_heap_queue *heap_q, t_coder *coder, t_config *conf)
{
	if (!heap_q || !coder || !conf || heap_q->size >= heap_q->capacity)
		return ;
	(heap_q->coders)[heap_q->size] = coder;
	heap_q->size ++;
	sort_tab(heap_q, conf);
}

t_coder	*heap_pop(t_heap_queue *heap_q, t_coder *coder)
{
	if (!coder || !heap_q || !heap_q->size)
		return (NULL);
	if (coder == heap_q->coders[0])
	{
		(heap_q->coders)[0] = (heap_q->coders)[1];
		(heap_q->coders)[1] = NULL;
	}
	else if (coder == heap_q->coders[1])
		heap_q->coders[1] = NULL;
	else
		return (NULL);
	heap_q->size --;
	return (coder);
}
