/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_codexion.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 23:58:17 by varandri          #+#    #+#             */
/*   Updated: 2026/08/29 00:40:40 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_CODEXION_H
# define HEADER_CODEXION_H
# include "header_struct.h"

long			ft_atol(char *nbr);
long			print_action(t_coder *coder, t_config *conf, char *action);
t_arg			*new_arg(t_coder *coder, t_dongle *dongle,
					t_coder *coders, t_config *conf);
long			get_time(struct timeval *time);

void			edf_sort(t_heap_queue *queue, t_config *conf);
void			fifo_sort(t_heap_queue *queue);
t_heap_queue	*new_heap_q(int capacity, int size);
void			heap_push(t_heap_queue *heap_q, t_coder *coder, t_config *conf);
t_coder			*heap_pop(t_heap_queue *heap_q, t_coder *coder);

void			init_config(int argc, char **argv, t_config **conf);
void			init_coders(int numbers, t_coder **coders, t_config *conf);
t_monitor		*init_monitor(t_coder	*coders, t_config *conf);

int				is_priority(t_coder *coder);
int				is_donlges_available(t_coder *coder);
void			request_dognles(t_coder *coder, t_config *conf);
void			fail_safe_cool_down(void *c_arg);
void			take_dongles(t_coder *coder, t_config *conf);
void			release_dongles(t_coder *coder, t_config *conf);
void			compile(t_coder *coder, t_config *conf);
void			debug(t_coder *coder, t_config *conf);
void			refactor(t_coder *coder, t_config *conf);

#endif