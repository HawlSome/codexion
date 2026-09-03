/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 17:54:34 by varandri          #+#    #+#             */
/*   Updated: 2026/09/03 13:05:41 by varandri         ###   ########.fr       */
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

long	get_time(t_config *conf)
{
	struct timeval	*time;
	struct timeval	now;

	if (!conf)
		return (0);
	gettimeofday(&now, NULL);
	time = &conf->t_0;
	return (
		(now.tv_sec - time->tv_sec) * 1000
		+ (now.tv_usec - time->tv_usec) / 1000
	);
}

long	print_action(t_coder *coder, t_config *conf, char *action)
{
	long	now_ms;

	if (!coder || !conf || !action)
		return (0);
	pthread_mutex_lock(&conf->action_lock);
	now_ms = get_time(conf);
	printf("%li %i %s\n", now_ms, coder->id, action);
	pthread_mutex_unlock(&conf->action_lock);
	return (now_ms);
}

void	msleep(t_config *conf, long time)
{
	long	start;

	if (!conf)
		return ;
	start = get_time(conf);
	while (!is_stop(conf) && (get_time(conf) - start) < time)
		usleep(1000);
}
