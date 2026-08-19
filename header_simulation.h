/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_simulation.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 13:19:41 by varandri          #+#    #+#             */
/*   Updated: 2026/08/19 21:47:53 by varandri         ###   ########.fr       */
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

void	start_threads(t_coder *coders, t_config *conf);
void	join_threads(t_coder *coders);

#endif