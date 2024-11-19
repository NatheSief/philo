/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlebecq <xlebecq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 09:28:06 by xlebecq           #+#    #+#             */
/*   Updated: 2024/11/19 14:59:19 by xlebecq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_get_args(t_cfg *s, int argc, const char **argv)
{
	if (argc != 5 && argc != 6)
		ft_error_msg(ERROR0, NULL, 0);
	s->nb_philo = ft_atoi(argv[1]);
	s->time_to_die = ft_atoi(argv[2]);
	s->time_to_eat = ft_atoi(argv[3]);
	s->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		s->meals_required = ft_atoi(argv[5]);
	else
		s->meals_required = 0;
	if (s->nb_philo < 1 || s->nb_philo > 200)
		ft_error_msg(ERROR1, NULL, 0);
	if (s->time_to_die < 60 || s->time_to_eat < 60 || s->time_to_sleep < 60)
		ft_error_msg(ERROR2, NULL, 0);
}

void	ft_init_philo(t_cfg *s)
{
	size_t	i;

	i = 0;
	s->philo = NULL;
	s->philo = (t_philo *)malloc(sizeof(*(s->philo)) * \
s->nb_philo);
	if (!s->philo)
		ft_error_msg(ERROR3, NULL, 0);
	while (i < s->nb_philo)
	{
		s->philo[i].id = i;
		s->philo[i].eating = 0;
		s->philo[i].l_fork = i;
		s->philo[i].r_fork = (i + 1) % s->nb_philo;
		s->philo[i].eat_count = 0;
		s->philo[i].s = s;
		i++;
	}
}

void	ft_init_mutex(t_cfg *s)
{
	size_t	i;

	i = 0;
	s->forks_mutex = (pthread_mutex_t *)malloc(sizeof(*(s->forks_mutex)) * \
s->nb_philo);
	if (!s->forks_mutex)
		ft_error_msg(ERROR4, s, 0);
	while (i < s->nb_philo)
	{	
		if (pthread_mutex_init(&s->forks_mutex[i], NULL) != 0)
			ft_error_msg(ERROR5, s, 1);
		if (pthread_mutex_init(&s->philo[i].mutex, NULL) != 0)
			ft_error_msg(ERROR6, s, 1);
		if (pthread_mutex_init(&s->philo[i].eating_mutex, NULL) != 0)
			ft_error_msg(ERROR7, s, 1);
		if (pthread_mutex_lock(&s->philo[i].eating_mutex) != 0)
			ft_error_msg(ERROR8, s, 1);
		i++;
	}
	if (pthread_mutex_init(&s->display_mutex, NULL) != 0)
		ft_error_msg(ERROR9, s, 1);
	if (pthread_mutex_init(&s->dead_mutex, NULL) != 0)
		ft_error_msg(ERROR10, s, 1);
	if (pthread_mutex_lock(&s->dead_mutex) != 0)
		ft_error_msg(ERROR11, s, 1);
}

void	ft_free(t_cfg *s, int mutex)
{
	size_t	i;

	i = 0;
	if (!s)
		return ;
	if (s->forks_mutex)
	{
		while (i < s->nb_philo)
			pthread_mutex_destroy(&s->forks_mutex[i++]);
		free(s->forks_mutex);
	}
	i = 0;
	if (s->philo)
	{
		while (i < s->nb_philo)
		{
			pthread_mutex_destroy(&s->philo[i].mutex);
			pthread_mutex_destroy(&s->philo[i++].eating_mutex);
		}
		free (s->philo);
	}
	if (mutex == 1)
	{
		pthread_mutex_destroy(&s->display_mutex);
		pthread_mutex_destroy(&s->dead_mutex);
	}
}

void	ft_create_threads(t_cfg *s)
{
	s->time = ft_time();
}

uint64_t	ft_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (((uint64_t)(current_time.tv_sec) * 1000)
		+ ((uint64_t)(current_time.tv_usec) / 1000));
}

int	main(int argc, const char **argv, char **envp)
{
	t_cfg	s;

	ft_get_args(&s, argc, argv);
	ft_init_philo(&s);
	ft_init_mutex(&s);
	ft_create_threads(&s);
	ft_free(&s, 1);
	return (0);
}
