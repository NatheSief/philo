/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlebecq <xlebecq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:22:51 by xlebecq           #+#    #+#             */
/*   Updated: 2024/11/07 11:25:37 by xlebecq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <stdint.h>

struct s_sphilosophers;

typedef struct	s_dining_cfg
{
	struct s_philosophers	*philosophers;
	int			number_of_philosophers;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int			nb_of_times_each_philosopher_must_eat;
	pthread_mutex_t		*m_forks;
	pthread_mutex_t		m_write;
	pthread_mutex_t		m_dead;
}	t_dining_cfg;

typedef struct	s_philosophers
{
	t_dining_cfg	*dining_cfg;
	int		id;
	uint64_t	time_since_eat;
	int		eating;
	uint64_t	time_limit;
	int		eat_count;
	int		l_fork;
	int		r_fork;
	pthread_mutex_t	m_mutex;
	pthread_mutex_t	m_eating;
}	t_philosophers;

void	ft_error_msg(const char *msg);
int	ft_atoi(const char *str);

#endif
