/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_helpers.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 10:24:45 by varandri          #+#    #+#             */
/*   Updated: 2026/08/19 21:45:14 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_HELPERS_H
# define HEADER_HELPERS_H
# include "header_queu.h"

int		is_there_burn_out(t_coder *coders);
int		get_dongles(t_coder *coder);
int		release_dongles(t_coder *coder);
void	compile(void);
void	refactor(void);
void	debug(void);

#endif