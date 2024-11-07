/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlebecq <xlebecq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 09:28:06 by xlebecq           #+#    #+#             */
/*   Updated: 2024/11/07 06:49:49 by xlebecq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	get_args(t_dining_cfg *dining_cfg, int argc, const char **argv)
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

int	main(int argc, const char **argv)
{
	t_dining_cfg	dining_cfg;
	t_philosophers	*philosophers;

	get_args(&dining_cfg, argc, argv);
	philosophers = (t_philosophers *)malloc(sizeof(t_philosophers *) * dining_cfg.number_of_philosophers);
/*	printf("number_of_philosophers = %d\ntime_to_die = %lu\n\
time_to_eat = %lu\ntime_to_sleep = %lu\nnb_of_times_each_philosopher_must_eat =\
 %d\n", dining_cfg.number_of_philosophers, dining_cfg.time_to_die, \
dining_cfg.time_to_eat, dining_cfg.time_to_sleep, \
dining_cfg.nb_of_times_each_philosopher_must_eat);*/
	return (0);
}
