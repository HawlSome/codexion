/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 00:02:34 by varandri          #+#    #+#             */
/*   Updated: 2026/08/23 18:12:46 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_codexion.h"

static t_config	*new_config(void)
{
	t_config	*conf;

	conf = (t_config *)malloc(sizeof(t_config));
	if (!conf)
		return (NULL);
	conf->burnout_time = 0;
	conf->coders_count = 0;
	conf->compile_required = 0;
	conf->compile_time = 0;
	conf->debug_time = 0;
	conf->dongle_cool_down = 0;
	conf->refactor_time = 0;

	return (conf);
}

static int	*parse_config(int argc, char **argv)
{
	int	*arg_conf;
	int	i;

	if (argc != 9 || !*argv || !argv)
		return (NULL);
	arg_conf = (int *)malloc((argc - 2 * sizeof(int)));
	if (!arg_conf)
		return (NULL);
	i = 1;
	while (i < argc - 1)
	{
		arg_conf[i - 1] = ft_atol(argv[i]);
		i ++;
	}
	return (arg_conf);
}

static void	set_config(int argc, char **argv, t_config *conf, int *arg_conf)
{
	if (!conf || !arg_conf)
		return ;
	conf->coders_count = arg_conf[0];
	conf->burnout_time = arg_conf[1];
	conf->compile_time = arg_conf[2];
	conf->debug_time = arg_conf[3];
	conf->refactor_time = arg_conf[4];
	conf->compile_required =  arg_conf[5];
	conf->dongle_cool_down = arg_conf[6];
	conf->scheduler = argv[argc - 1];
}

void	init_config(int argc, char **argv, t_config **conf)
{
	int		*arg_conf;

	*conf = NULL;
	arg_conf = parse_config(argc, argv);
	if (!arg_conf)
		return ;
	*conf = new_config();
	set_config(argc, argv, *conf, arg_conf);
	free(arg_conf);
}
