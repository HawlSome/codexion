/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_codexion.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 23:58:17 by varandri          #+#    #+#             */
/*   Updated: 2026/09/04 12:22:59 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_CODEXION_H
# define HEADER_CODEXION_H
# include "header_struct.h"

void			program_clean(t_coder *coder, t_config *conf);

long			ft_atol(char *nbr);
t_arg			*new_arg(t_coder *coder, t_dongle *dongle,
					t_coder *coders, t_config *conf);
long			get_time(t_config *conf);
long			print_action(t_coder *coder, t_config *conf, char *action);
void			msleep(t_config *conf, long time);

void			edf_sort(t_heap_queue *queue, t_config *conf);
void			fifo_sort(t_heap_queue *queue);
t_heap_queue	*new_heap_q(int capacity, int size);
void			heap_push(t_heap_queue *heap_q, t_coder *coder, t_config *conf);
t_coder			*heap_pop(t_heap_queue *heap_q, t_coder *coder);

void			init_config(int argc, char **argv, t_config **conf);
void			init_coders(t_coder **coders, t_config *conf);
int				is_valid_coders(t_coder *coders, t_config *conf);
void			print_error(long *arg_conf);

int				is_priority(t_coder *coder);
int				is_donlges_available(t_coder *coder);
void			request_dongles(t_coder *coder, t_config *conf);
void			fail_safe_cool_down(void *c_arg);
void			join_cool_down(t_dongle *dongle);
void			take_dongles(t_coder *coder, t_config *conf);
void			init_cooldown(t_coder *coder, t_config *conf);
void			release_dongles(t_coder *coder, t_config *conf);

int				is_stop(t_config *conf);
void			set_stop(t_config *conf);
int				simulation_stop(t_config *conf);
void			start_monitoring(pthread_t *monitor, t_config *conf,
					t_coder *coders);
void			start_coders_routines(t_coder *coders, t_config *conf);
void			end_coders_routines(t_coder *coder);

#endif