/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlebecq <xlebecq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:22:51 by xlebecq           #+#    #+#             */
/*   Updated: 2024/11/18 11:52:26 by xlebecq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/*----------------------------------------------------------------------------*/
/*							         INCLUDES                                 */
/*----------------------------------------------------------------------------*/

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <stdint.h>
# include <sys/time.h>

/*----------------------------------------------------------------------------*/
/*									STRUCTURES								  */
/*----------------------------------------------------------------------------*/

typedef struct s_dining_cfg
{
	struct s_philosophers	*philosophers;
	int						nb_of_philosophers;
	uint64_t				time_to_die;
	uint64_t				time_to_eat;
	uint64_t				time_to_sleep;
	uint64_t				time;
	int						nb_of_times_each_philosopher_must_eat;
	pthread_mutex_t			*forks_mutex;
	pthread_mutex_t			display_mutex;
	pthread_mutex_t			dead_mutex;
}	t_dining_cfg;

typedef struct s_philosophers
{
	t_dining_cfg	*s;
	int				id;
	uint64_t		time_since_eat;
	int				eating;
	uint64_t		time_limit;
	int				eat_count;
	int				l_fork;
	int				r_fork;
	pthread_mutex_t	mutex;
	pthread_mutex_t	eating_mutex;
}	t_philosophers;

/*----------------------------------------------------------------------------*/
/*						    		FUNCTIONS                                 */
/*----------------------------------------------------------------------------*/

void		ft_error_msg(const char *msg, t_dining_cfg *s, int i);
int			ft_atoi(const char *str);
uint64_t	ft_time(void);
void		ft_free(t_dining_cfg *s, int mutex);

#endif
