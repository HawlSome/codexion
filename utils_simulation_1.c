/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_simulation_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 15:13:35 by varandri          #+#    #+#             */
/*   Updated: 2026/09/03 13:04:09 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_codexion.h"

void	end_coders_routines(t_coder *coder)
{
	while (coder)
	{
		pthread_join(coder->thread, NULL);
		coder = coder->next;
	}
}
