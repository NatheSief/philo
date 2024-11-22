/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlebecq <xlebecq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 09:33:12 by xlebecq           #+#    #+#             */
/*   Updated: 2024/11/22 13:06:10 by xlebecq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_error_msg(const char *msg, t_cfg *s)
{
	while (*msg)
		write(2, msg++, 1);
	ft_free_array(s);
	exit(EXIT_FAILURE);
}

void	ft_handle_sign(const char *str, int *i)
{
	while (str[*i] == ' ' || (str[*i] >= 9 && str[*i] <= 13))
		(*i)++;
	if (str[*i] == '-')
		ft_error_msg(ERROR_NEGATIVE_ARGS, NULL);
	else if (str[*i] == '+')
		(*i)++;
}

void	ft_overflow(long long result, int digit)
{
	if (result > (INT_MAX - digit) / 10)
		ft_error_msg(ERROR_OVERFLOW, NULL);
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
		ft_error_msg(ERROR_INVALID_CHARACTERS, NULL);
	return ((int)(result));
}

uint64_t	ft_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (((uint64_t)(current_time.tv_sec) * 1000)
		+ ((uint64_t)(current_time.tv_usec) / 1000));
}
