/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlebecq <xlebecq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:22:51 by xlebecq           #+#    #+#             */
/*   Updated: 2024/11/19 16:25:28 by xlebecq          ###   ########.fr       */
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

typedef struct s_cfg
{
	struct s_philo			*philo;
	size_t					nb_philo;
	uint64_t				time_to_die;
	uint64_t				time_to_eat;
	uint64_t				time_to_sleep;
	uint64_t				time;
	int						meals_required;
	pthread_mutex_t			*forks_mutex;
	pthread_mutex_t			display_mutex;
	pthread_mutex_t			dead_mutex;
}	t_cfg;

typedef struct s_philo
{
	t_cfg	*s;
	int				id;
	uint64_t		time_since_eat;
	int				eating;
	uint64_t		time_limit;
	int				eat_count;
	int				l_fork;
	int				r_fork;
	pthread_mutex_t	mutex;
	pthread_mutex_t	eating_mutex;
}	t_philo;

/*----------------------------------------------------------------------------*/
/*						    		FUNCTIONS                                 */
/*----------------------------------------------------------------------------*/

void		ft_error_msg(const char *msg, t_cfg *s);
int			ft_atoi(const char *str);
uint64_t	ft_time(void);
void		ft_free_array(t_cfg *s);

# define ERROR0 	"Error: Invalid number of arguments.\n"
# define ERROR1 	"Error: Nb of philosophers must beetween 1 and 200.\n"
# define ERROR2 	"Error: time_to_die, time_to_eat, and time_to_sleep must be at least 60ms.\n"
# define ERROR3 	"Error: Memory allocation failed for philosophers.\n"
# define ERROR4 	"Error: Memory allocation failed for forks_mutex.\n"
# define ERROR5		"Error: Failed to initialize forks_mutex.\n"
# define ERROR6		"Error: Failed to initialize mutex mutex.\n"
# define ERROR7		"Error: Failed to initialize eating_mutex.\n"
# define ERROR8		"Error: Failed to lock eating_mutex.\n"
# define ERROR9 	"Error: Failed to initialize display_mutex.\n"
# define ERROR10 	"Error: Failed to initialize dead_mutex.\n"
# define ERROR11	"Error: Failed to lock dead_mutex.\n"
# define ERROR12	"Error: Argument must be a positive number.\n"
# define ERROR13	"Error: Argument exceeds maximum integer value.\n"
# define ERROR14	"Error: Argument contains invalid characters.\n"

#endif
