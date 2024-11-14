/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlebecq <xlebecq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 09:28:06 by xlebecq           #+#    #+#             */
/*   Updated: 2024/11/14 19:17:52 by xlebecq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_get_args(t_dining_cfg *dining_cfg, int argc, const char **argv)
{
	if (argc < 5 || argc > 6)
		ft_error_msg("Error : invalid number of arguments.\n");
	dining_cfg->number_of_philosophers = ft_atoi(argv[1]);
	dining_cfg->time_to_die = ft_atoi(argv[2]);
	dining_cfg->time_to_eat = ft_atoi(argv[3]);
	dining_cfg->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		dining_cfg->nb_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		dining_cfg->nb_of_times_each_philosopher_must_eat = 0;
	if (dining_cfg->number_of_philosophers < 1
		|| dining_cfg->number_of_philosophers > 200)
		ft_error_msg("Error : Number of philosophers must\
 beetween 1 and 200.\n");
	if (dining_cfg->time_to_die < 60 || dining_cfg->time_to_eat < 60
		|| dining_cfg->time_to_sleep < 60)
		ft_error_msg("Error : time_to_die, time_to_eat, and\
 time_to_sleep must be at least 60ms.\n");
}

void	ft_init_philosophers(t_dining_cfg *dining_cfg)
{
	int	i;

	i = 0;
	while (i < dining_cfg->number_of_philosophers)
	{
		dining_cfg->philosophers[i].id = i;
		dining_cfg->philosophers[i].eating = 0;
		dining_cfg->philosophers[i].l_fork = i;
		dining_cfg->philosophers[i].r_fork = (i + 1) % dining_cfg->number_of_philosophers;
		dining_cfg->philosophers[i].eat_count = 0;
		dining_cfg->philosophers[i].dining_cfg  = dining_cfg;
		i++;
	}
}

void	ft_init_mutex(t_dining_cfg dining_cfg)
{
	int i;

	i = 0;
	while (i < dining_cfg->number_of_philosophers)
	{
		pthread_mutex_init(&dining_cfg->philosophers[i].mutex, NULL);
		phtread_mutex_init(&dining_cfg->philosophers[i].eating_mutex, NULL);
		phtread_mutex_lock(&dining_cfg->philosophers[i].eating_mutex);

	}
	dining_cfg->forks_mutex = (pthread_mutex_t *)malloc(sizeof(*(dining_cfg->forks_mutex)) * dining_cfg->number_of_philosophers);
	pthread_mutex_init(&dining_cfg->display_mutex, NULL);
	pthread_mutex_init(&dining_cfg->dead_mutex, NULL);
	phtread_mutex_lock(&dining_cfg->dead_mutex);
	
}

int	main(int argc, const char **argv)
{
	t_dining_cfg	dining_cfg;

	dining_cfg.philosophers = NULL;
	ft_get_args(&dining_cfg, argc, argv);
	dining_cfg.philosophers = (t_philosophers *)malloc(sizeof(*(dining_cfg.philosophers)) * dining_cfg.number_of_philosophers);
	if (!dining_cfg.philosophers)
		ft_error_msg("Error: Memory allocation failed for philosophers.\n");
	ft_init_philosophers(&dining_cfg);
	ft_init_mutex(&dining_cfg);
	return (0);
}
