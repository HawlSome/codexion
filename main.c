/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 07:35:57 by varandri          #+#    #+#             */
/*   Updated: 2026/08/30 16:34:57 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_codexion.h"

int	main(int argc, char **argv)
{
	pthread_t	monitor;
	t_config	*conf;
	t_coder		*coder;

	coder = NULL;
	conf = NULL;
	init_config(argc, argv, &conf);
	init_coders(&coder, conf);
	if (!is_valid_coders(coder, conf))
	{
		program_clean(coder, conf);
		return (0);
	}
	gettimeofday(&conf->t_0, NULL);
	start_monitoring(&monitor, conf, coder);
	start_coders_routines(coder, conf);
	end_coders_routines(coder);
	set_stop(conf);
	pthread_join(monitor, NULL);
	program_clean(coder, conf);
	return (0);
}
