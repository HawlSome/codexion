/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 07:35:57 by varandri          #+#    #+#             */
/*   Updated: 2026/08/17 11:20:05 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_queu.h"

int	main(int argc, char **argv)
{
	t_config	*conf;
	t_coder		*coder;

	create_config(argc, argv, &conf);
	if (!conf)
		return (0);
	create_coders(conf->coders_count, &coder);
	set_coders(coder, conf);
	printf("%i", (coder->next)->number);
	free(conf);
	return (0);
}
