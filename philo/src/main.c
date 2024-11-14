/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlebecq <xlebecq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 09:28:06 by xlebecq           #+#    #+#             */
/*   Updated: 2024/11/14 22:44:23 by xlebecq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_get_args(t_dining_cfg *s, int argc, const char **argv)
{
	if (argc < 5 || argc > 6)
		ft_error_msg("Error : invalid number of arguments.\n");
	s->nb_of_philosophers = ft_atoi(argv[1]);
	s->time_to_die = ft_atoi(argv[2]);
	s->time_to_eat = ft_atoi(argv[3]);
	s->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		s->nb_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		s->nb_of_times_each_philosopher_must_eat = 0;
	if (s->nb_of_philosophers < 1 || s->nb_of_philosophers > 200)
		ft_error_msg("Error: Nb of philosophers must beetween 1 and 200.\n");
	if (s->time_to_die < 60 || s->time_to_eat < 60 || s->time_to_sleep < 60)
		ft_error_msg("Error : time_to_die, time_to_eat, and\
 time_to_sleep must be at least 60ms.\n");
}

void	ft_init_philosophers(t_dining_cfg *s)
{
	int	i;

	i = 0;
	s->philosophers = NULL;
	s->philosophers = (t_philosophers *)malloc(sizeof(*(s->philosophers)) * \
s->nb_of_philosophers);
	if (!s->philosophers)
		ft_error_msg("Error: Memory allocation failed for philosophers.\n");
	while (i < s->nb_of_philosophers)
	{
		s->philosophers[i].id = i;
		s->philosophers[i].eating = 0;
		s->philosophers[i].l_fork = i;
		s->philosophers[i].r_fork = (i + 1) % s->nb_of_philosophers;
		s->philosophers[i].eat_count = 0;
		s->philosophers[i].s = s;
		i++;
	}
}

void	ft_init_mutex(t_dining_cfg *s)
{
	int	i;

	i = 0;
	s->forks_mutex = (pthread_mutex_t *)malloc(sizeof(*(s->forks_mutex)) * \
s->nb_of_philosophers);
	if (!s->forks_mutex)
		ft_error_msg("Error: Memory allocation failed for mutex.\n");
	while (i < s->nb_of_philosophers)
	{	
		pthread_mutex_init(&s->forks_mutex[i], NULL);
		pthread_mutex_init(&s->philosophers[i].mutex, NULL);
		pthread_mutex_init(&s->philosophers[i].eating_mutex, NULL);
		pthread_mutex_lock(&s->philosophers[i].eating_mutex);
		i++;
	}
	pthread_mutex_init(&s->display_mutex, NULL);
	pthread_mutex_init(&s->dead_mutex, NULL);
	pthread_mutex_lock(&s->dead_mutex);
}

int	main(int argc, const char **argv)
{
	t_dining_cfg	s;

	ft_get_args(&s, argc, argv);
	ft_init_philosophers(&s);
	ft_init_mutex(&s);
	return (0);
}
