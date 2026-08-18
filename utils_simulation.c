/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 10:05:05 by varandri          #+#    #+#             */
/*   Updated: 2026/08/18 10:16:05 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_simulation.h"

t_arg	*new_arg(void)
{
	t_arg	*arg;

	arg = (t_arg *)malloc(sizeof(t_arg));
	if (!arg)
		return (NULL);
	arg->config = NULL;
	arg->coder = NULL;
	return (arg);
}

void	*coder_routine(void *arg)
{
	t_arg	*coder_conf;

	coder_conf = (t_arg *) arg;
	return (NULL);
}