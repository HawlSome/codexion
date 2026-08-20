/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 13:16:34 by varandri          #+#    #+#             */
/*   Updated: 2026/08/20 07:30:07 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_config.h"

static t_config	*new_config(void)
{
	t_config	*config;

	config = (t_config *)malloc(sizeof(t_config));
	if (!config)
		return (NULL);
	config->coders_count = 0;
	config->burnout_time = 0;
	config->compile_time = 0;
	config->debug_time = 0;
	config->refactor_time = 0;
	config->compile_required = 0;
	config->dongle_cool_down = 0;
	config->scheduler = NULL;
	return (config);
}

static int	*parse_config(int argc, char **argv, char **scheduler)
{
	int	*arg_conf;
	int	i;

	if (argc != 9 || !*argv || !argv)
		return (NULL);
	arg_conf = (int *)malloc((argc - 2) * sizeof(int));
	if (!arg_conf)
		return (NULL);
	i = 1;
	while (i < argc - 1)
	{
		arg_conf[i - 1] = atoi(argv[i]);
		i++;
	}
	*scheduler = argv[argc - 1];
	return (arg_conf);
}

static void	set_config(t_config *config, int *arg_conf, char *scheduler)
{
	if (!config)
		return ;
	config->coders_count = arg_conf[0];
	config->burnout_time = arg_conf[1];
	config->compile_time = arg_conf[2];
	config->debug_time = arg_conf[3];
	config->refactor_time = arg_conf[4];
	config->compile_required = arg_conf[5];
	config->dongle_cool_down = arg_conf[6];
	config->scheduler = scheduler;
}

void	create_config(int argc, char **argv, t_config **config)
{
	int		*arg_conf;
	char	*scheduler;

	*config = NULL;
	arg_conf = parse_config(argc, argv, &scheduler);
	if (!arg_conf)
		return ;
	*config = new_config();
	set_config(*config, arg_conf, scheduler);
	pthread_mutex_init(&((*config)->mutex), NULL);
	pthread_cond_init(&((*config)->cond), NULL);
	free(arg_conf);
}
