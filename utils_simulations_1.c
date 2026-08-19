/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_simulations_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 01:37:58 by varandri          #+#    #+#             */
/*   Updated: 2026/08/20 01:49:27 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_simulation.h"

void	start_queu(t_queu **queu, t_coder *coders)
{
	(*queu) = NULL;
	while (coders)
	{
		queu_add_last(queu, coders);
		coders = coders->next;
	}
}

void	join_threads(t_coder *coders)
{
	while (coders)
	{
		pthread_join(coders->thread, NULL);
		coders = coders->next;
	}
}
