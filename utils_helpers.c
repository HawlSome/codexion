/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 10:25:50 by varandri          #+#    #+#             */
/*   Updated: 2026/08/18 11:24:59 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_helpers.h"

int     get_dongles(t_coder *coder)
{
	if (!coder || !(coder->l_dongle) || !(coder->r_dongle))
		return (0);
	if (!(coder->l_dongle)->is_used && !(coder->r_dongle)->is_used)
	{
		(coder->l_dongle)->is_used = 1;
		(coder->r_dongle)->is_used = 1;
		
		return (1);
	}
	return (0);
}
