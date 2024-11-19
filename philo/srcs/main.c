/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlebecq <xlebecq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 09:28:06 by xlebecq           #+#    #+#             */
/*   Updated: 2024/11/19 19:12:55 by xlebecq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_parse_args(t_cfg *s, int argc, const char **argv)
{
	if (argc != 5 && argc != 6)
		ft_error_msg(ERROR_ARGS, NULL);
	s->nb_philo = ft_atoi(argv[1]);
	s->time_to_die = ft_atoi(argv[2]);
	s->time_to_eat = ft_atoi(argv[3]);
	s->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		s->meals_required = ft_atoi(argv[5]);
	else
		s->meals_required = 0;
	if (s->nb_philo < 1 || s->nb_philo > 200)
		ft_error_msg(ERROR_NB_PHILO, NULL);
	if (s->time_to_die < 60 || s->time_to_eat < 60 || s->time_to_sleep < 60)
		ft_error_msg(ERROR_LIMIT_ARGS, NULL);
}

void	ft_init_philo(t_cfg *s)
{
	size_t	i;

	i = 0;
	s->philo = NULL;
	s->philo = (t_philo *)malloc(sizeof(*(s->philo)) * \
s->nb_philo);
	if (!s->philo)
		ft_error_msg(ERROR_MALLOC_PHILO, NULL);
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
		ft_error_msg(ERROR_MALLOC_MUTEX, s);
	while (i < s->nb_philo)
	{	
		if (pthread_mutex_init(&s->forks_mutex[i], NULL) != 0)
			ft_error_msg(ERROR_FORKS_MUTEX, s);
		if (pthread_mutex_init(&s->philo[i].mutex, NULL) != 0)
			ft_error_msg(ERROR_MUTEX_MUTEX, s);
		if (pthread_mutex_init(&s->philo[i].eating_mutex, NULL) != 0)
			ft_error_msg(ERROR_EATING_MUTEX, s);
		if (pthread_mutex_lock(&s->philo[i].eating_mutex) != 0)
			ft_error_msg(ERROR_EATING_MUTEX_LOCK, s);
		i++;
	}
	if (pthread_mutex_init(&s->display_mutex, NULL) != 0)
		ft_error_msg(ERROR_DISPLAY_MUTEX, s);
	if (pthread_mutex_init(&s->dead_mutex, NULL) != 0)
		ft_error_msg(ERROR_DEAD_MUTEX, s);
	if (pthread_mutex_lock(&s->dead_mutex) != 0)
		ft_error_msg(ERROR_DEAD_MUTEX_LOCK, s);
}

void	ft_free_array(t_cfg *s)
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
}

void	ft_destroy_mutex(t_cfg *s)
{
	pthread_mutex_destroy(&s->display_mutex);
	pthread_mutex_destroy(&s->dead_mutex);
}

void	ft_create_threads(t_cfg *s)
{
	size_t		i;
	pthread_t	tid;

	i = 0;
	s->time = ft_time();
	if (s->meals_required > 0)
	{
		if (pthread_create(&tid, NULL, &ft_meals_monitor, (void *)s) != 0)
			ft_error_msg(ERROR_MEALS_MONITOR_CREATE, s);
		pthread_detach(tid);
	}
	while (i < s->nb_philo)
	{
		if (pthread_create(&tid, NULL, &ft_start_routine, (void *)&s->philo[i++]) != 0)
			ft_error_msg(ERROR_START_ROUTINE_CREATE, s);
		pthread_detach(tid);
		usleep(100);
	}
}

void	*ft_meals_monitor(void *s)
{
	(void)s;
	printf("TEST MEAL");
	return (NULL);
}

void	*ft_start_routine(void *s)
{
	(void)s;
	printf("TEST ROUTINE");
	return (NULL);
}

uint64_t	ft_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (((uint64_t)(current_time.tv_sec) * 1000)
		+ ((uint64_t)(current_time.tv_usec) / 1000));
}

int	main(int argc, const char **argv)
{
	t_cfg	s;

	ft_parse_args(&s, argc, argv);
	ft_init_philo(&s);
	ft_init_mutex(&s);
	ft_create_threads(&s);
	ft_free_array(&s);
	return (0);
}
