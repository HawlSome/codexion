/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   healpers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 17:54:34 by varandri          #+#    #+#             */
/*   Updated: 2026/08/24 09:25:16 by varandri         ###   ########.fr       */
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
