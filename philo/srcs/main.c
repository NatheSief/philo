/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlebecq <xlebecq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 09:28:06 by xlebecq           #+#    #+#             */
/*   Updated: 2024/11/21 23:57:47 by xlebecq          ###   ########.fr       */
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
	if (argv[5])
		s->meals_required = ft_atoi(argv[5]);
	else
		s->meals_required = 0;
	if (s->nb_philo < 1 || s->nb_philo > 200)
		ft_error_msg(ERROR_NB_PHILO);
	if (s->time_to_die < 60 || s->time_to_eat < 60 || s->time_to_sleep < 60)
		ft_error_msg(ERROR_LIMIT_ARGS);
	s->time = 0;
	s->over = 0;
	s->ready = 0;
}

void	ft_init_philo(t_cfg *s)
{
	size_t	i;

	i = -1;
	s->philo = (t_philo *)malloc(sizeof(*(s->philo)) * s->nb_philo);
	if (!s->philo)
		ft_error_msg(ERROR_MALLOC_PHILO);
	while (++i < s->nb_philo)
	{
		s->philo[i].id = i;
		s->philo[i].eating = 0;
		s->philo[i].eat_count = 0;
		s->philo[i].s = s;
		s->philo[i].l_fork = &s->forks_mutex[i];
		s->philo[i].r_fork = 0;
	}
}

void	ft_init_mutex(t_cfg *s)
{
	size_t	i;

	s->forks_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * \
			s->nb_philo);
	if (!s->forks_mutex)
		ft_error_msg(ERROR_MALLOC_FORKS_MUTEX);
	i = -1;
	while (++i < s->nb_philo)
		if (pthread_mutex_init(&s->forks_mutex[i], NULL) != 0)
			ft_error_msg(ERROR_FORKS_MUTEX);
	s->dead_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(s->dead_mutex, NULL) != 0)
		ft_error_msg(ERROR_DEAD_MUTEX);
}

void	ft_create_thread(t_cfg *s)
{
	size_t	i;

	i = -1;
	
	s->time = ft_time();
	while (++i < s->nb_philo)
	{
		s->philo[i].start_time = s->time;
		s->philo[i].meals = s->time;
	}
	i = -1;
	while (++i < s->nb_philo)
	{
		s->philo[i].r_fork = s->philo[(i + 1) % s->nb_philo].l_fork;
		if (pthread_create(&s->philo[i].tid, NULL, &ft_start_routine, \
					s) != 0)
			ft_error_msg(ERROR_START_ROUTINE_CREATE);
	}
	s->ready = 1;
}

void	*ft_start_routine(void *s)
{
	t_cfg	*cfg;

	cfg = (t_cfg *)s;
	while (!cfg->ready)
		continue;
	if (cfg->philo->id & 1)
		ft_usleep(cfg->time_to_eat * 0.9 + 1);
	while(!cfg->over)
	{
		printf("while\n");
		ft_eat(cfg);
	}
	return (NULL);
}

void	ft_eat(t_cfg *s)
{
	pthread_mutex_lock(s->philo->l_fork);
	printf ("TEST\n");
	ft_display(s,FORK);
	pthread_mutex_unlock(s->philo->l_fork);

}

void	ft_display(t_cfg *s, const char *str)
{
	//pthread_mutex_lock(s->dead_mutex);
	printf ("s-time > %ld\n", ft_time());
	printf ("start_time > %ld\n", s->philo->start_time);
	printf ("%ldms %d %s\n", ft_time() - s->philo->start_time, s->philo->id, str);
	//pthread_mutex_unlock(s->dead_mutex);*/

}

int	main(int argc, const char **argv)
{
	t_cfg	s;
	size_t	i;

	i = 0;
	ft_parse_args(&s, argc, argv);
	printf("parse ok\n");
	ft_init_philo(&s);
	printf("init_philo ok\n");
	ft_init_mutex(&s);
	printf("init_mutex ok\n");
	ft_create_thread(&s);
	printf("create_thread ok\n");
	return (0);
}
