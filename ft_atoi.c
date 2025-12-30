/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaaz <hlaaz@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 04:17:07 by hlaaz             #+#    #+#             */
/*   Updated: 2025/12/30 09:44:37 by hlaaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int ft_atoi(const char *str)
{
    long result = 0;
    int sign = 1;
    int i = 0;

	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
		result = result * 10 + (str[i++] - '0');
	if ((result * sign) < INT_MIN || (result * sign) > INT_MAX)
		exit_error();
	return ((int)(result * sign));
}
void	check_degit(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i] && (str[i] < '0' ||str[i] > '9'))
		{
			if ((str[i] >= 9 && str[i] <= 13) || str[i] == 32 || (str[i] == '-' || str[i] == '+'))
				i++;
			else
				exit_error();
		}
		else
			i++;
	}
	return ;
}
