/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_simulation.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 13:19:41 by varandri          #+#    #+#             */
/*   Updated: 2026/08/19 21:43:03 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_SIMULATION_H
# define HEADER_SIMULATION_H
# include "header_helpers.h"

typedef struct s_arg
{
	t_config	*config;
	t_coder		*coder;
	t_coder		*coders;
}		t_arg;

t_arg	*new_arg(void);
void	*coder_routine(void *arg);

#endif