/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_queu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 23:26:24 by varandri          #+#    #+#             */
/*   Updated: 2026/08/20 01:45:04 by varandri         ###   ########.fr       */
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

static int	in_queu(t_queu *queu, t_coder *coder)
{
	while (queu)
	{
		if ((queu->coder)->id == coder->id)
			return (1);
		queu = queu->next;
	}
	return (0);
}

void	queu_add_last(t_queu **queu, t_coder *coder)
{
	t_queu	*last;

	if (!coder || in_queu(*queu, coder))
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
