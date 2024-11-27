/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlebecq <xlebecq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:22:51 by xlebecq           #+#    #+#             */
/*   Updated: 2024/11/27 11:37:25 by xlebecq          ###   ########.fr       */
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
	int					nb_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					meals_required;
	int			beginning_time;
	int					ready;
	int					check_meals;
	int					end;
	pthread_mutex_t		check_ready;
	pthread_mutex_t		check_end;
	pthread_mutex_t		*forks_mutex;
	pthread_mutex_t		*dead_mutex;
}	t_cfg;

typedef struct s_philo
{
	int					id;
	int					dead;
	int					meals_count;
	int			last_meal;
	int			philo_start_time;
	pthread_t			tid;
	pthread_mutex_t			*l_fork;
	pthread_mutex_t			*r_fork;
	t_cfg				*st;
}	t_philo;

/*----------------------------------------------------------------------------*/
/*		                         FUNCTIONS                                    */
/*----------------------------------------------------------------------------*/

void		ft_error_msg(const char *msg);
int			ft_atoi(const char *str);
int	ft_time(void);
void		*ft_start_routine(void *s);
void		ft_eat(t_philo *philo);
void		ft_display(t_philo *philo, char *str);
int		ft_usleep(int time);
void		ft_sleep(t_philo *s);
int		ft_dead(t_philo *philo);
int		ft_count(t_philo philo, int i);
int		ft_print_dead(t_philo *philo);
int	ft_check_end(t_cfg *s);

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
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

#endif
