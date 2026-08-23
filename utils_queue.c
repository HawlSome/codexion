/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_queue.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 00:02:39 by varandri          #+#    #+#             */
/*   Updated: 2026/08/23 18:39:11 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_codexion.h"

static t_coder	**create_tab_coders(int capacity)
{
	t_coder **tab_coder;

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
	if (!strcmp(conf->scheduler, "edf"))
		edf_sort(queue, conf);
	if (!strcmp(conf->scheduler, "fifo"))
		fifo_sort(queue);
}

t_heap_queue	*new_heap_q(int capacity, int size)
{
	t_heap_queue	*heapq;

	heapq = (t_heap_queue *)malloc(sizeof(t_heap_queue));
	if (!heapq)
		return (NULL);
	heapq->capacity = capacity;
	heapq->size = size;
	heapq->coders = create_tab_coders(capacity);
}

void		heap_push(t_heap_queue *heap_q, t_coder *coder, t_config *conf)
{
	if (!heap_q || !coder || !conf)
		return ;
	(heap_q->coders)[heap_q->size] = coder;
	heap_q->size += 1;
	sort_tab(heap_q, conf);
}