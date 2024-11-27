/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlebecq <xlebecq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 09:33:12 by xlebecq           #+#    #+#             */
/*   Updated: 2024/11/26 22:59:10 by xlebecq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_error_msg(const char *msg)
{
	while (*msg)
		write(2, msg++, 1);
	exit(EXIT_FAILURE);
}

void	ft_handle_sign(const char *str, int *i)
{
	while (str[*i] == ' ' || (str[*i] >= 9 && str[*i] <= 13))
		(*i)++;
	if (str[*i] == '-')
		ft_error_msg(ERROR_NEGATIVE_ARGS);
	else if (str[*i] == '+')
		(*i)++;
}

void	ft_overflow(long long result, int digit)
{
	if (result > (INT_MAX - digit) / 10)
		ft_error_msg(ERROR_OVERFLOW);
}

int	ft_atoi(const char *str)
{
	int			i;
	long long	result;
	int			digit;

	i = 0;
	result = 0;
	ft_handle_sign(str, &i);
	while (str[i] >= '0' && str[i] <= '9')
	{
		digit = str[i] - '0';
		ft_overflow(result, digit);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		ft_error_msg(ERROR_INVALID_CHARACTERS);
	return ((int)(result));
}

int	ft_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000)
		+ (current_time.tv_usec / 1000));
}

int	ft_usleep(int time)
{
	int	start_time;

	start_time = ft_time();
	while ((ft_time() - start_time) < time)
		usleep(150);
	return (1);
}
void	ft_display(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->st->dead_mutex);
	if (ft_check_end(philo->st))
	{
		pthread_mutex_unlock(philo->st->dead_mutex);
		return ;
	}
	printf ("%dms %d %s\n", ft_time() - philo->philo_start_time, philo->id, str);

	pthread_mutex_unlock(philo->st->dead_mutex);

}
