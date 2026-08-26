/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 00:30:40 by varandri          #+#    #+#             */
/*   Updated: 2026/08/27 00:32:50 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_codexion.h"

long	get_elapsed_ms(struct timeval *time)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (
		(now.tv_sec - time->tv_sec) * 1000
		+ (now.tv_usec - time->tv_usec) / 1000
	);
}
