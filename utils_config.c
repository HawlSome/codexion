/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varandri <varandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 00:02:34 by varandri          #+#    #+#             */
/*   Updated: 2026/09/05 06:49:21 by varandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_codexion.h"

static int	is_invalid_arg(long *arg_conf)
{
	int	i;

	if (!arg_conf)
		return (1);
	i = 0;
	while (i < 7)
	{
		if (arg_conf[i] < 0)
			return (1);
		i++;
	}
	return (0);
}

static t_config	*new_config(void)
{
	t_config	*conf;

	conf = (t_config *)malloc(sizeof(t_config));
	if (!conf)
		return (NULL);
	conf->stop = 0;
	conf->burnout_time = 0;
	conf->coders_count = 0;
	conf->compile_required = 0;
	conf->compile_time = 0;
	conf->debug_time = 0;
	conf->dongle_cool_down = 0;
	conf->refactor_time = 0;
	pthread_mutex_init(&conf->general_lock, NULL);
	pthread_mutex_init(&conf->stop_lock, NULL);
	pthread_mutex_init(&conf->action_lock, NULL);
	pthread_cond_init(&conf->general_cond, NULL);
	gettimeofday(&conf->t_0, NULL);
	return (conf);
}

static long	*parse_config(int argc, char **argv)
{
	long	*arg_conf;
	int		i;

	if (argc != 9 || !*argv || !argv)
		return (NULL);
	arg_conf = (long *)malloc(((argc - 2) * sizeof(long)));
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

static void	set_config(int argc, char **argv, t_config *conf, long *arg_conf)
{
	if (!conf || !arg_conf)
		return ;
	conf->coders_count = arg_conf[0];
	conf->burnout_time = arg_conf[1];
	conf->compile_time = arg_conf[2];
	conf->debug_time = arg_conf[3];
	conf->refactor_time = arg_conf[4];
	conf->compile_required = arg_conf[5];
	conf->dongle_cool_down = arg_conf[6];
	conf->scheduler = argv[argc - 1];
}

void	init_config(int argc, char **argv, t_config **conf)
{
	long		*arg_conf;

	*conf = NULL;
	arg_conf = parse_config(argc, argv);
	if (!arg_conf || is_invalid_arg(arg_conf)
		|| !arg_conf[0] || arg_conf[0] > 300 || !arg_conf[2] || !arg_conf[3]
		|| !arg_conf[4] || !arg_conf[5]
		|| (strcmp(argv[argc - 1], "edf") && strcmp(argv[argc - 1], "fifo")
			&& strcmp(argv[argc - 1], "EDF") && strcmp(argv[argc - 1], "FIFO"))
	)
	{
		print_error(arg_conf);
		free(arg_conf);
		return ;
	}
	*conf = new_config();
	set_config(argc, argv, *conf, arg_conf);
	free(arg_conf);
}
