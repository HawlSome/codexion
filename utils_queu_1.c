/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_queu_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 01:24:16 by varandri          #+#    #+#             */
/*   Updated: 2026/08/20 01:48:53 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_queu.h"

void	queu_remove_elem(t_queu	**queu, t_coder *coder)
{
	t_queu	*q;
	t_queu	*next;

	if (!queu || !*queu || !coder)
		return ;
	q = *queu;
	while (q && q->coder && (q->coder)->id == coder->id)
	{
		next = q->next;
		free(q);
		q = next;
	}
	*queu = q;
	while (q)
	{
		next = q->next;
		while (next && next->coder && (next->coder)->id == coder->id)
		{
			q->next = next->next;
			free (next);
			next = q->next ;
		}
		q = q->next;
	}
}
