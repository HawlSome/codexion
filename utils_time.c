/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 00:30:40 by varandri          #+#    #+#             */
/*   Updated: 2026/08/24 09:41:10 by varandri         ###   ########.fr       */
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

long	get_time_ms(struct timeval *time)
{
	return ((long)((time->tv_sec) * 1000 + (time->tv_usec) / 1000));
}

long	get_elapsed_deadline(struct timeval *last_compile_start,
			long burn_out_time)
{
	if (!last_compile_start)
		return (0);
	return (get_time_ms(last_compile_start) + burn_out_time);
}
