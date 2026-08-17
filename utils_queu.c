/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_queu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 23:26:24 by varandri          #+#    #+#             */
/*   Updated: 2026/08/17 12:55:54 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_queu.h"

static t_queu	*new_queu(t_coder *coder)
{
	t_queu	*new_queu;

	if (!coder)
		return (NULL);
	new_queu = (t_queu *) malloc(sizeof(t_queu));
	if (!new_queu)
		return (NULL);
	new_queu->coder = coder;
	new_queu->next = NULL;
	return (new_queu);
}

static t_queu	*last_queu(t_queu *queu)
{
	while (queu && queu->next)
		queu = queu->next;
	return (queu);
}

void	queu_add_last(t_queu **queu, t_coder *coder)
{
	t_queu	*last;

	if (!coder)
		return ;
	last = last_queu(*queu);
	if (!last)
		*queu = new_queu(coder);
	else
		last->next = new_queu(coder);
}

void	queu_remove_first(t_queu **queu)
{
	t_queu	*first;

	if (!queu || !*queu)
		return ;
	first = *queu;
	*queu = (*queu)->next;
	free (first);
}

void	queu_remove_elem(t_queu	**queu, t_coder *coder)
{
	t_queu	*q;
	t_queu	*next;

	if (!queu || !*queu || !coder)
		return ;
	q = *queu;
	while (q && q->coder && (q->coder)->number == coder->number)
	{
		next = q->next;
		free(q);
		q = next;
	}
	*queu = q;
	while (q)
	{
		next = q->next;
		while (next && next->coder && (next->coder)->number == coder->number)
		{
			q->next = next->next;
			free (next);
			next = q->next ;
		}
		q = q->next;
	}
}
