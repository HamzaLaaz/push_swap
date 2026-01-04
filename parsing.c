/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaaz <hlaaz@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 11:40:21 by hlaaz             #+#    #+#             */
/*   Updated: 2026/01/04 16:29:49 by hlaaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	check_digits(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (1);
	if (str[i] == '-' || str[i] == '+')
	{
		i++;
		if (!str[i])
			return (1);
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

static int	check_duplicates(t_node *stack, int new_val)
{
	if (!stack)
		return (0);
	while (stack)
	{
		if (stack->value == new_val)
			return (1);
		stack = stack->next;
	}
	return (0);
}

static void	checker(t_node **stack_a, char **strs, int j)
{
	long	val;

	val = ft_atol(strs[j]);
	if (val > 2147483647 || val < (-2147483648))
		exit_with_error(stack_a, strs);
	if (check_duplicates(*stack_a, (int)val))
		exit_with_error(stack_a, strs);
	add_node_back(stack_a, (int)val);
}

void	parsing_argv(int argc, char **argv, t_node **stack_a)
{
	char	**strs;
	int		i;
	int		j;

	i = 1;
	while (i < argc)
	{
		strs = ft_split(argv[i], ' ');
		if (!strs || !*strs)
			exit_with_error(stack_a, strs);
		j = 0;
		while (strs[j])
		{
			if (check_digits(strs[j]))
				exit_with_error(stack_a, strs);
			checker(stack_a, strs, j);
			j++;
		}
		free_split(strs);
		i++;
	}
}
