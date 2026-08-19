/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 10:05:05 by varandri          #+#    #+#             */
/*   Updated: 2026/08/19 21:44:08 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_simulation.h"

static t_arg	*new_arg(void)
{
	t_arg	*arg;

	arg = (t_arg *)malloc(sizeof(t_arg));
	if (!arg)
		return (NULL);
	arg->config = NULL;
	arg->coder = NULL;
	arg->coders = NULL;
	return (arg);
}

static void	coders_actions(t_coder *coder)
{
	/*verif if it has the priority*/
	/*if its not the priority stay in the queu*/
	/*verif if it can take dongle*/
	/*if it can take a dongle wait the dongle cool-down*/
	/*take_dongle();*/
	/*compile();*/
	/*debug();*/
	/*refactor();*/
	return ;
}

static void	*coder_routine(void *r_arg)
{
	t_arg	*arg;

	arg = (t_arg *) r_arg;
	while ((arg->coder)->required_compilation
		&& is_there_burn_out(arg->coders))
	{
		break ;
	}
	printf("hello");
	free(r_arg);
	return (NULL);
}

void	start_threads(t_coder *coders, t_config *conf)
{
	t_coder	*coder;
	t_arg	*arg;

	coder = coders;
	while (coder && conf)
	{
		arg = new_arg();
		arg->config = conf;
		arg->coder = coder;
		arg->coders = coders;
		pthread_create(&(coder->thread), NULL,
			coder_routine, (void *)arg);
		coder = coder->next;
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
