/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlebecq <xlebecq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:22:51 by xlebecq           #+#    #+#             */
/*   Updated: 2024/11/05 22:19:07 by xlebecq          ###   ########.fr       */
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

typedef struct	s_dining_cfg
{
	int		number_of_philosophers;
	uint64_t	time_to_die;
	uint64_t	time_to_eat;
	uint64_t	time_to_sleep;
	int		nb_of_times_each_philosopher_must_eat;
}	t_dining_cfg;

typedef struc	s_philosophers
{
	int	id;
}	t_philosophers

void	ft_error_msg(const char *msg);
int	ft_atoi(const char *str);

#endif
