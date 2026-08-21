/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_codexion.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 23:58:17 by varandri          #+#    #+#             */
/*   Updated: 2026/08/21 12:56:40 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_CODEXION_H
# define HEADER_CODEXION_H
# include "header_struct.h"

long			get_elapsed_ms(struct timeval *time);

t_heap_queue	*new_heap_q(int capacity, int size);

void	init_config(int argc, char **argv, t_config **conf);
void	init_coders(int numbers, t_coder **coders);

#endif