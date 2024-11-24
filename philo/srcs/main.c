/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlebecq <xlebecq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 09:28:06 by xlebecq           #+#    #+#             */
/*   Updated: 2024/11/24 21:24:08 by xlebecq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_parse_args(t_cfg *s, int argc, const char **argv)
{
	if (argc != 5 && argc != 6)
		ft_error_msg(ERROR_ARGS);
	s->nb_philo = ft_atoi(argv[1]);
	s->time_to_die = ft_atoi(argv[2]);
	s->time_to_eat = ft_atoi(argv[3]);
	s->time_to_sleep = ft_atoi(argv[4]);
	s->meals_required = 0;
	s->check_meals = 0;
	s->ready = 0;
	s->end = 0;
	s->beginning_time = 0;
	if (argv[5])
	{
		s->check_meals = 1;
		s->meals_required = ft_atoi(argv[5]);
	}
	if (s->nb_philo < 1 || s->nb_philo > 200)
		ft_error_msg(ERROR_NB_PHILO);
	if (s->time_to_die < 60 || s->time_to_eat < 60 || s->time_to_sleep < 60)
		ft_error_msg(ERROR_LIMIT_ARGS);
}

void	ft_init_mutex(t_cfg *s)
{
	size_t	i;

	s->dead_mutex = 0;
	s->forks_mutex = 0;
	s->forks_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * s->nb_philo);
	if (!s->forks_mutex)
		ft_error_msg(ERROR_MALLOC_FORKS_MUTEX);
	i = 0;
	while (i < s->nb_philo)
	{
		if (pthread_mutex_init(&s->forks_mutex[i], NULL) != 0)
			ft_error_msg(ERROR_FORKS_MUTEX);
		i++;
	}
	s->dead_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(s->dead_mutex, NULL) != 0)
		ft_error_msg(ERROR_DEAD_MUTEX);
}

void	ft_init_philo(t_philo *philo, t_cfg *s)
{
	size_t	i;

	i = 0;
	philo = (t_philo *)malloc(sizeof(t_philo) * philo->s->nb_philo);
	if (!philo)
		ft_error_msg(ERROR_MALLOC_PHILO);
	while (i < s->nb_philo)
	{
		philo[i].id = i;
		printf ("id -> %ld\n", philo[i].id);
		philo[i].dead = 0;
		philo[i].meals_count = 0;
		philo[i].philo_start_time = 0;
		philo[i].last_meal = 0;
		philo[i].s = s;
		philo[i].l_fork = &s->forks_mutex[i];
		philo[i].r_fork = 0;
		i++;
	}
}

void	ft_create_thread(t_cfg *s, t_philo *philo)
{
	size_t	i;

	i = 0;
	
	while (i < s->nb_philo)
	{
		s->philo[i].r_fork = s->philo[(i + 1) % s->nb_philo].l_fork;
		if (pthread_create(&s->philo[i].tid, NULL, (void *)&ft_start_routine, (void *)&s->philo[i]) != 0)
			ft_error_msg(ERROR_START_ROUTINE_CREATE);
		i++;
		printf("pthread create -> %ld est cree\n", i);
	}
	
	i = 0;
	s->beginning_time = ft_time();
	while (i < s->nb_philo)
	{
		s->philo[i].philo_start_time = s->beginning_time;
		s->philo[i].last_meal = s->beginning_time;
		i++;
	}
	s->ready = 1;
}

void	*ft_start_routine(void *structure)
{
	t_philo	*philo;

	philo = (t_philo *)structure;
	
	while (!philo->s->ready)
		continue;
	printf ("START ROUTINE\n");
	if (philo->id & 1)
		ft_usleep(philo->s->time_to_eat * 0.9 + 1);
	while(!philo->s->end)
	{
		ft_eat(philo->s);
		ft_sleep(philo->s);
	}	
	return (NULL);
}

void	ft_eat(t_cfg *s)
{
	pthread_mutex_lock(s->philo->l_fork);
	ft_display(s, FORK);
	pthread_mutex_lock(s->philo->r_fork);
	ft_display(s, FORK);
	s->philo->last_meal = ft_time();
	ft_usleep(s->time_to_eat);
	ft_display(s, EAT);
	s->philo->meals_count++;
	pthread_mutex_unlock(s->philo->l_fork);
	pthread_mutex_unlock(s->philo->r_fork);
}

void	ft_sleep(t_cfg *s)
{
	ft_usleep(s->time_to_sleep);
	ft_display(s, SLEEP);
	ft_display(s, THINK);
}

void	ft_ctrl_thread(t_cfg *s)
{
	size_t	i;

	i = 0;
	while (!s->ready)
		continue;
	while (!s->end)
	{
		i = 0;
		while (i < s->nb_philo)
			if (ft_dead(&s->philo[i]) || ft_count(&s->philo[i], i))
				s->end = 1;
	}
	if (s->check_meals && s->philo[s->nb_philo -1].meals_count == s->meals_required)
	{
		ft_usleep(5 * s->nb_philo);
		printf("                         \n");
		printf("   Complete ");
	}
}

int	ft_dead(t_philo *philo)
{
	uint64_t	time;

	pthread_mutex_lock(philo->s->dead_mutex);
	time = ft_time() - philo->last_meal;
	if (time >= philo->s->time_to_die)
	{
		pthread_mutex_unlock(philo->s->dead_mutex);
		return(ft_print_dead(philo));
	}
	pthread_mutex_unlock(philo->s->dead_mutex);
	return (0);
}

int	ft_count(t_philo *philo, size_t i)
{
	if (philo->s->check_meals && i == philo->s->nb_philo -1 && philo->meals_count == philo->s->meals_required)
		return (ft_usleep(300));
	return (0);
}

int	ft_print_dead(t_philo *philo)
{
	ft_display(philo->s, DIE);
	philo->s->end = 1;
	philo->dead = 1;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}

static void	ft_finish_thread(t_cfg *s)
{
	size_t i;

	i = 0;
	while (i < s->nb_philo)
	{
		pthread_join(s->philo[i].tid, (void *)&s->philo[i]);
		i++;
	}
	pthread_mutex_destroy(s->dead_mutex);
	pthread_mutex_destroy(s->forks_mutex);
	free(s->dead_mutex);
	free(s->forks_mutex);
	free(s->philo);
}

int	main(int argc, const char **argv)
{
	t_cfg	s;
	t_philo philo;

	ft_parse_args(&s, argc, argv);
	ft_init_mutex(&s);
	ft_init_philo(&philo, &s);
	ft_create_thread(&s);
	ft_ctrl_thread(&s);
	ft_finish_thread(&s);
	return (0);
}
