/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlebecq <xlebecq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 09:28:06 by xlebecq           #+#    #+#             */
/*   Updated: 2024/11/23 15:14:09 by xlebecq          ###   ########.fr       */
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
	if (argv[5])
		s->meals_required = ft_atoi(argv[5]);
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

	i = 0;
	s->philo = (t_philo *)malloc(sizeof(*(s->philo)) * s->nb_philo);
	if (!s->philo)
		ft_error_msg(ERROR_MALLOC_PHILO);
	printf("philo %ld\n", s->nb_philo);
	while (i < s->nb_philo)
	{
		s->philo[i].id = i;
		s->philo[i].eating = 0;
		s->philo[i].eat_count = 0;
		s->philo[i].s = s;
		s->philo[i].l_fork = &s->forks_mutex[i];
		s->philo[i].r_fork = 0;
		i++;
	}
}

void	ft_init_mutex(t_cfg *s)
{
	size_t	i;

	s->forks_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * \
			s->nb_philo);
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

void	ft_create_thread(t_cfg *s)
{
	size_t	i;

	i = 0;
	
	s->ready = 1;
	while (i < s->nb_philo)
	{
		s->philo[i].r_fork = s->philo[(i + 1) % s->nb_philo].l_fork;
		if (pthread_create(&s->philo[i].tid, NULL, (void *)ft_start_routine, (void *)s) != 0)
			ft_error_msg(ERROR_START_ROUTINE_CREATE);
		i++;
		printf("pthread create -> %ld est cree\n", i);
	}
	
	i = 0;
	s->time = ft_time();
	while (i < s->nb_philo)
	{
		s->philo[i].start_time = s->time;
		s->philo[i].meals = s->time;
		i++;
	}
	s->ready = 1;
}

void	*ft_start_routine(void *s)
{
	t_cfg	*cfg;

	cfg = (t_cfg *)s;
	
	while (cfg->ready)
	 	continue;
	printf("philo id : %d\n", cfg->philo->id);
	printf("philo nb : %ld\n", cfg->nb_philo);
	printf("struct adress : %p\n", cfg);
	if (cfg->philo->id & 1)
		ft_usleep(cfg->time_to_eat * 0.9 + 1);
	while(!cfg->over)
	{
		ft_eat(cfg);
	}	
	return (NULL);
}

void	ft_eat(t_cfg *s)
{
	pthread_mutex_lock(s->philo->l_fork);
	ft_display(s, FORK);
	pthread_mutex_lock(s->philo->r_fork);
	ft_display(s, FORK);
	s-meals = ft_time();
	ft_usleep(s->time_to_eat);
	ft_display(s, EAT);
	pthread_mutex_unlock(s->philo->l_fork);
	pthread_mutex_unlock(s->philo->r_fork);
}

void	ft_display(t_cfg *s, const char *str)
{
	pthread_mutex_lock(s->dead_mutex);
	printf ("%ldms %d %s\n", ft_time() - s->philo->start_time, s->philo->id, str);
	pthread_mutex_unlock(s->dead_mutex);

}

int	main(int argc, const char **argv)
{
	t_cfg	s;
	size_t	i;

	i = 0;
	ft_parse_args(&s, argc, argv);
	ft_init_philo(&s);
	ft_init_mutex(&s);
	ft_create_thread(&s);
	for (i = 0; i < s.nb_philo; i++)
    	{
        	if (pthread_join(s.philo[i].tid, NULL) != 0)
        	{
            		perror("pthread_join failed");
            		exit(EXIT_FAILURE);
        	}
    	}
	return (0);
}
