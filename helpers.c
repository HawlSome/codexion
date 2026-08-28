/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 17:54:34 by varandri          #+#    #+#             */
/*   Updated: 2026/08/29 01:09:06 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_codexion.h"

long	ft_atol(char *nbr)
{
	long	result;
	int		sign;
	int		i;

	if (!nbr)
		return (-1);
	i = 0;
	sign = 1;
	while (nbr[i] && (nbr[i] == ' ' || (nbr[i] >= 9 && nbr[i] <= 13)))
		i ++;
	if (nbr[i] && (nbr[i] == '-' || nbr[i] == '+'))
	{
		if (nbr[i] == '-')
			sign = -sign;
		i ++;
	}
	result = 0;
	while (nbr[i] && nbr[i] >= '0' && nbr[i] <= '9')
	{
		result = result * 10 + (nbr[i] - '0');
		i ++;
	}
	if (nbr[i] && !(nbr[i] >= '0' && nbr[i] <= '9'))
		return (-1);
	return (sign * result);
}

long	print_action(t_coder *coder, t_config *conf, char *action)
{
	long	now_ms;

	if (!coder || !conf || !action)
		return (0);
	now_ms = get_time(&conf->t_0);
	printf("%li %i %s", now_ms, coder->id, action);
	return (now_ms);
}

t_arg	*new_arg(t_coder *coder, t_dongle *dongle,
	t_coder *coders, t_config *conf)
{
	t_arg	*arg;

	arg = (t_arg *)malloc(sizeof(t_arg));
	if (!arg)
		return (NULL);
	arg->coder = coder;
	arg->dongle = dongle;
	arg->coders = coders;
	arg->conf = conf;
	return (arg);
}

long	get_time(struct timeval *time)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (
		(now.tv_sec - time->tv_sec) * 1000
		+ (now.tv_usec - time->tv_usec) / 1000
	);
}
