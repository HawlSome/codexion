/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_codexion.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 23:58:17 by varandri          #+#    #+#             */
/*   Updated: 2026/08/24 09:25:33 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_CODEXION_H
# define HEADER_CODEXION_H
# include "header_struct.h"

long			ft_atol(char *nbr);

long			get_elapsed_ms(struct timeval *time);
long			get_time_ms(struct timeval *time);
long			get_elapsed_deadline(struct timeval *last_compile_start,
					long burn_out_time);

void			edf_sort(t_heap_queue *queue, t_config *conf);
void			fifo_sort(t_heap_queue *queue);
t_heap_queue	*new_heap_q(int capacity, int size);
void			heap_push(t_heap_queue *heap_q, t_coder *coder, t_config *conf);

void			init_config(int argc, char **argv, t_config **conf);
void			init_coders(int numbers, t_coder **coders);
t_monitor		*init_monitor(t_coder	*coders, t_config *conf);

#endif