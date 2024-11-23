/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlebecq <xlebecq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:22:51 by xlebecq           #+#    #+#             */
/*   Updated: 2024/11/23 20:48:41 by xlebecq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/*----------------------------------------------------------------------------*/
/*			                     INCLUDES                                     */
/*----------------------------------------------------------------------------*/

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <stdint.h>
# include <sys/time.h>

/*----------------------------------------------------------------------------*/
/*                               STRUCTURES	            	                  */
/*----------------------------------------------------------------------------*/

typedef struct s_cfg
{
	struct s_philo	*philo;
	size_t			nb_philo;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	uint64_t		over;
	size_t			meals_required;
	uint64_t		time;
	size_t			ready;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	*dead_mutex;
}	t_cfg;

typedef struct s_philo
{
	int				id;
	int				nb;
	uint64_t		meals;
	uint64_t		start_time;
	int				eating;
	int				eat_count;
	pthread_t		tid;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_cfg			*s;
}	t_philo;

/*----------------------------------------------------------------------------*/
/*		                         FUNCTIONS                                    */
/*----------------------------------------------------------------------------*/

void		ft_error_msg(const char *msg);
int			ft_atoi(const char *str);
uint64_t	ft_time(void);
void		*ft_start_routine(void *s);
void		ft_eat(t_cfg *s);
void		ft_display(t_cfg *s, const char *str);
int			ft_usleep(uint64_t time);

/*----------------------------------------------------------------------------*/
/*			                   ERRORS_MESSAGES                                */
/*----------------------------------------------------------------------------*/

# define ERROR_ARGS 				"Error: Invalid number of arguments.\n"
# define ERROR_NB_PHILO 			"Error: Nb of philosophers must beetween 1 \
and 200.\n"
# define ERROR_LIMIT_ARGS			"Error: time_to_die, time_to_eat, and \
time_to_sleep must be at least 60ms.\n"
# define ERROR_MALLOC_PHILO 		"Error: Memory allocation failed for \
philosophers.\n"
# define ERROR_MALLOC_FORKS_MUTEX	"Error: Memory allocation failed for forks_\
mutex.\n"
# define ERROR_FORKS_MUTEX			"Error: Failed to initialize forks_mutex.\n"
# define ERROR_MUTEX_MUTEX			"Error: Failed to initialize mutex mutex.\n"
# define ERROR_EATING_MUTEX			"Error: Failed to initialize eating_mutex.\n"
# define ERROR_EATING_MUTEX_LOCK	"Error: Failed to lock eating_mutex.\n"
# define ERROR_DISPLAY_MUTEX		"Error: Failed to initialize display_\
mutex.\n"
# define ERROR_DEAD_MUTEX			"Error: Failed to initialize dead_mutex.\n"
# define ERROR_DEAD_MUTEX_LOCK		"Error: Failed to lock dead_mutex.\n"
# define ERROR_NEGATIVE_ARGS		"Error: Argument must be a positive \
number.\n"
# define ERROR_OVERFLOW				"Error: Argument exceeds maximum integer \
value.\n"
# define ERROR_INVALID_CHARACTERS	"Error: Argument contains invalid \
characters.\n"
# define ERROR_MEALS_MONITOR_CREATE	"Error: Failed to create thread ft_meals_\
monitor.\n"
# define ERROR_START_ROUTINE_CREATE	"Error: Failed to create thread ft_start_\
routine.\n"

# define FORK "has taken a fork"
# define FORK "is eating"

#endif
