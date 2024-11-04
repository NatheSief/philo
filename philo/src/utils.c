/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlebecq <xlebecq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 09:33:12 by xlebecq           #+#    #+#             */
/*   Updated: 2024/11/04 06:40:42 by xlebecq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_error_msg(const char *msg)
{
	while (*msg)
		write(2, msg++, 1);
	exit(EXIT_FAILURE);
}

int	ft_atoi(const char *nbr)
{
	int		i;
	int		sign;
	long long	result;
	int		digit;

	i = 0;
	sign = 1;
	result = 0;
	ft_handle_sign(nbr, &i);
	digit = nbr[i] - '0';
	while (nbr[i] >= '0' && nbr[i] <= '9')
	{
		(\ft_overflow(result, digit)
			ft_error_msg("Error: argument is too large and causes overflow.\n");
		result = result * 10 + (nbr[i] - '0')
		if (result > INT_MAX)
		i++;
	}
	

void	ft_handle_sign(char *nbr, int *i)
{
	while(nbr[*i] == ' ' || src[*i] >= 9 && src[*i] <= 13)
		(*i)++;
	if (nbr[*i] == '-')
		ft_error_msg("Error: argument must be a positive number.\n");
	else if (src[*i] == '+')
		(*i)++;
}


	
