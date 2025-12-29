/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaaz <hlaaz@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 04:17:07 by hlaaz             #+#    #+#             */
/*   Updated: 2025/12/29 08:45:16 by hlaaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long ft_atol(const char *str)
{
    long result = 0;
    int sign = 1;
    int i = 0;

    while (str[i] >= 9 && str[i] <= 13 || str[i] == 32) //! check if the string have just space
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
    while (str[i])
		result = result * 10 + (str[i++] - '0');
    return (result * sign);
}
