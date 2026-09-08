/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_verifier.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 02:59:10 by varandri          #+#    #+#             */
/*   Updated: 2026/09/05 07:03:48 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_codexion.h"

static long	coders_count(t_coder *coders)
{
	long	count;

	count = 0;
	while (coders)
	{
		count ++;
		coders = coders->next;
	}
	return (count);
}

void	print_error(long *arg_conf)
{
	if (!arg_conf)
	{
		printf("Error [args]: Invalid number of arguments (must be 8).");
		return ;
	}
	if (!arg_conf[2] || !arg_conf[3] || !arg_conf[4] || !arg_conf[5])
	{
		printf("Error [args]: Compilation | Debug | Refactor - time "
			"or required compilation value must be a positive number .\n");
	}
	else if (!arg_conf[0] || arg_conf[0] > 300)
		printf("Error [coders counts]: Coders count"
			" must be between 0 and 300.\n");
	else
		printf("Error [args]: Invalid arguments format. "
			"(Arguments must be positive numbers except the last one "
			"that must be 'fifo' or 'edf')\n");
}

static int	is_valid_dongles(t_dongle *l_dongle, t_dongle *r_dongle)
{
	if (!l_dongle && !r_dongle)
		return (0);
	if (!l_dongle->queue && !r_dongle->queue)
		return (0);
	if (!l_dongle->queue->coders && !r_dongle->queue->coders)
		return (0);
	return (1);
}

int	is_valid_coders(t_coder *coders, t_config *conf)
{
	if (!coders || !conf)
		return (0);
	if (conf->coders_count != coders_count(coders))
		return (0);
	while (coders)
	{
		if (!is_valid_dongles(coders->l_dongle, coders->r_dongle))
			return (0);
		coders = coders->next;
	}
	return (1);
}
