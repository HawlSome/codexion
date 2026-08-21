/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_queue.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 00:02:39 by varandri          #+#    #+#             */
/*   Updated: 2026/08/21 11:45:51 by varandri         ###   ########.fr       */
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