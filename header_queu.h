/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_queu.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 23:15:54 by varandri          #+#    #+#             */
/*   Updated: 2026/08/20 01:45:19 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_QUEU_H
# define HEADER_QUEU_H
# include "header_coder.h"

typedef struct s_queue
{
	t_coder			*coder;
	struct s_queue	*next;
}		t_queu;

void	queu_add_last(t_queu **queu, t_coder *coder);
void	queu_remove_first(t_queu **queu);
void	queu_remove_elem(t_queu	**queu, t_coder *coder);

#endif
