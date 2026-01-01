/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaaz <hlaaz@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 11:40:21 by hlaaz             #+#    #+#             */
/*   Updated: 2026/01/01 15:30:55 by hlaaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	check_digits(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 0;
	while(str[i])
	{
		if (str[i] < '0' ||str[i] > '9')
		{
			if (str[i] == '-' || str[i] == '+')
				i++;
			else
				return (1);
		}
		else
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

// static long	checker(t_node **stack_a, char *str, long val)
// {
// 	val = ft_atol(strs);
// 	if (val > INT_MAX || val < INT_MIN)
// 		exit_with_error(stack_a, strs);
// 	if (check_duplicates(*stack_a, (int)val))
// 		exit_with_error(stack_a, strs);
// 	add_node_back(stack_a, (int)val);
// }

void	parsing_argv(int argc, char **argv, t_node **stack_a)
{
	char	**strs;
	long		val;
	int		i;
	int		j;

	i = 1;
	while (i < argc)
	{
		strs = ft_split(argv[i], ' ');
		if (!strs)
			exit_error();
		j = 0;
		while(strs[j])
		{
			if(check_digits(strs[j]))
				exit_with_error(stack_a, strs);
			val = ft_atol(strs[j]);
			if (val > INT_MAX || val < INT_MIN)
				exit_with_error(stack_a, strs);
			if (check_duplicates(*stack_a, (int)val))
				exit_with_error(stack_a, strs);
			add_node_back(stack_a, (int)val);
			j++;
		}
		free_split(strs);
		i++;
	}
}
