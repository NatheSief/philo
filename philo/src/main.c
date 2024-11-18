/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlebecq <xlebecq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 09:28:06 by xlebecq           #+#    #+#             */
/*   Updated: 2024/11/18 02:35:53 by xlebecq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_get_args(t_dining_cfg *s, int argc, const char **argv)
{
	if (argc < 5 || argc > 6)
		ft_error_msg("Error : invalid number of arguments.\n", NULL, 0);
	s->nb_of_philosophers = ft_atoi(argv[1]);
	s->time_to_die = ft_atoi(argv[2]);
	s->time_to_eat = ft_atoi(argv[3]);
	s->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		s->nb_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		s->nb_of_times_each_philosopher_must_eat = 0;
	if (s->nb_of_philosophers < 1 || s->nb_of_philosophers > 200)
		ft_error_msg("Error: Nb of philosophers must beetween 1 and 200.\n", \
NULL, 0);
	if (s->time_to_die < 60 || s->time_to_eat < 60 || s->time_to_sleep < 60)
		ft_error_msg("Error : time_to_die, time_to_eat, and\
 time_to_sleep must be at least 60ms.\n", NULL, 0);
}

void	ft_init_philosophers(t_dining_cfg *s)
{
	int	i;

	i = 0;
	s->philosophers = NULL;
	s->philosophers = (t_philosophers *)malloc(sizeof(*(s->philosophers)) * \
s->nb_of_philosophers);
	if (!s->philosophers)
		ft_error_msg("Error: Memory allocation failed for philosophers.\n", \
NULL, 0);
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
		ft_error_msg("Error: Memory allocation failed for mutex.\n", s, 0);
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

void	ft_free(t_dining_cfg *s, int mutex)
{
	int	i;

	i = 0;
	if (s->forks_mutex)
	{
		while (i < s->nb_of_philosophers)
			pthread_mutex_destroy(&s->forks_mutex[i++]);
		free(s->forks_mutex);
	}
	i = 0;
	if (s->philosophers)
	{
		while (i < s->nb_of_philosophers)
		{
			pthread_mutex_destroy(&s->philosophers[i].mutex);
			pthread_mutex_destroy(&s->philosophers[i++].eating_mutex);
		}
		free (s->philosophers);
	}
	if (mutex == 1)
	{
		pthread_mutex_destroy(&s->display_mutex);
		pthread_mutex_destroy(&s->dead_mutex);
	}
}

void	ft_create_threads(t_dining_cfg *s)
{
	s->time = ft_time();
}

uint64_t	ft_time(void)
{
	static struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (((uint64_t)(current_time.tv_sec) * 1000) + \
((uint64_t)(current_time.tv_usec) * 1000));
}

int	main(int argc, const char **argv)
{
	t_dining_cfg	s;

	ft_get_args(&s, argc, argv);
	ft_init_philosophers(&s);
	ft_init_mutex(&s);
	ft_create_threads(&s);
	ft_free(&s, 1);
	return (0);
}
