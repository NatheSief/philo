/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlebecq <xlebecq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 09:28:06 by xlebecq           #+#    #+#             */
/*   Updated: 2024/11/25 17:17:51 by xlebecq          ###   ########.fr       */
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
	s->meals_required = -2;
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
	int	i;

	s->dead_mutex = 0;
	s->forks_mutex = 0;
	s->forks_mutex = malloc(sizeof(pthread_mutex_t) * s->nb_philo);
	if (!s->forks_mutex)
		ft_error_msg(ERROR_MALLOC_FORKS_MUTEX);
	i = 0;
	while (i < s->nb_philo)
	{
		if (pthread_mutex_init(&s->forks_mutex[i], NULL) != 0)
			ft_error_msg(ERROR_FORKS_MUTEX);
		i++;
	}
	s->dead_mutex = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(s->dead_mutex, NULL) != 0)
		ft_error_msg(ERROR_DEAD_MUTEX);
}

void	ft_init_philo(t_philo *philo, t_cfg *s)
{
	int	i;

	i = 0;
	while (i < s->nb_philo)
	{
		philo[i].id = i;
		philo[i].dead = 0;
		philo[i].meals_count = 0;
		philo[i].philo_start_time = 0;
		philo[i].last_meal = 0;
		philo[i].st = s;
		philo[i].l_fork = &s->forks_mutex[i];
		philo[i].r_fork = 0;
		i++;
	}
	i = 0;
}

void	ft_create_thread(t_cfg *s, t_philo *philo)
{
	int	i;

	i = 0;
	
	while (i < s->nb_philo)
	{
		philo[i].r_fork = philo[(i + 1) % s->nb_philo].l_fork;
		if (pthread_create(&philo[i].tid, NULL, &ft_start_routine, &philo[i]) != 0)
			ft_error_msg(ERROR_START_ROUTINE_CREATE);
		i++;
		printf("pthread create -> %d est cree\n", i);
	}
	
	i = 0;
	s->beginning_time = ft_time();
	while (i < s->nb_philo)
	{
		philo[i].philo_start_time = s->beginning_time;
		philo[i].last_meal = s->beginning_time;
		i++;
	}
	s->ready = 1;
}

void	*ft_start_routine(void *structure)
{
	t_philo	*philo;

	philo = (t_philo *)structure;
	
	while (!philo->st->ready)
		continue;
	if (philo->id & 1)
		ft_usleep(philo->st->time_to_eat * 0.9 + 1);
	while(!philo->st->end)
	{
		ft_eat(philo);
		ft_sleep(philo);
	}	
	return (NULL);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	ft_display(philo, FORK);
	pthread_mutex_lock(philo->r_fork);
	ft_display(philo, FORK);
	philo->last_meal = ft_time();
	ft_usleep(philo->st->time_to_eat);
	ft_display(philo, EAT);
	philo->meals_count++;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	ft_sleep(t_philo *philo)
{
	ft_usleep(philo->st->time_to_sleep);
	ft_display(philo, SLEEP);
	ft_display(philo, THINK);
}

int	ft_ctrl_thread(t_cfg *s, t_philo *philo)
{
	int	i;

	i = 0;
	while (!s->ready)
		continue;
	while (!s->end)
	{
		i = -1;
		while (++i < s->nb_philo)
			if (ft_dead(&philo[i]) || ft_count(philo[i], i))
				s->end = 1;
	}
	if (s->check_meals && philo[s->nb_philo -1].meals_count == s->meals_required)
	{
		ft_usleep(5 * s->nb_philo);
		printf("                         \n");
		printf("   Complete ");
		return(1);
	}
	return (0);
}

int	ft_dead(t_philo *philo)
{
	int	time;

	pthread_mutex_lock(philo->st->dead_mutex);
	time = ft_time() - philo->last_meal;
	if (time >= philo->st->time_to_die)
	{
		pthread_mutex_unlock(philo->st->dead_mutex);
		return(ft_print_dead(philo));
	}
	pthread_mutex_unlock(philo->st->dead_mutex);
	return (0);
}

int	ft_count(t_philo philo, int i)
{
	if (philo.st->check_meals && i == philo.st->nb_philo -1 && philo.meals_count == philo.st->meals_required)
		return (ft_usleep(300));
	return (0);
}

int	ft_print_dead(t_philo *philo)
{
	ft_display(philo, DIE);
	philo->st->end = 1;
	philo->dead = 1;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}

static void	ft_finish_thread(t_cfg *s, t_philo *philo)
{
	int i;

	i = 0;
	while (i < s->nb_philo)
	{
		pthread_join(philo[i].tid, (void *)&philo[i]);
		i++;
	}
	pthread_mutex_destroy(s->dead_mutex);
	pthread_mutex_destroy(s->forks_mutex);
	free(s->dead_mutex);
	free(s->forks_mutex);
	free(philo);
}

void	ft_malloc_philo(t_cfg *s)
{
	t_philo *philo;	
	philo = malloc(sizeof(t_philo) * s->nb_philo);
	if (!philo)
		ft_error_msg(ERROR_MALLOC_PHILO);
	
	ft_init_philo(philo, s);
	ft_create_thread(s, philo);
	ft_ctrl_thread(s, philo);
	ft_finish_thread(s, philo);

}

int	main(int argc, const char **argv)
{
	t_cfg	s;

	ft_parse_args(&s, argc, argv);

//	ft_init_mutex(&s);

	
//	ft_malloc_philo(&s);
	return (0);
}
