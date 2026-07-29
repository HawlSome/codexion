/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 07:35:57 by varandri          #+#    #+#             */
/*   Updated: 2026/07/29 12:04:00 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_config.h"

int	main(int argc, char **argv)
{
	t_config	*conf;
	int			*arg_conf;
	char		*scheduler;

	conf = new_config();
	arg_conf = parse_config(argc, argv, &scheduler);
	if (!arg_conf)
		return (0);
	set_config(conf, arg_conf, scheduler);
	printf("%s", conf->scheduler);
	return (0);
}
