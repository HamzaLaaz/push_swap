/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaaz <hlaaz@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 11:40:21 by hlaaz             #+#    #+#             */
/*   Updated: 2025/12/31 15:43:22 by hlaaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void add_node_back(t_node **stack, int value)
{
    t_node *new_node;
    t_node *last;

    new_node = malloc(sizeof(t_node));
    if (!new_node)
        return ;
    new_node->value = value;
    new_node->next = NULL;
    if (*stack == NULL)
    {
        *stack = new_node;
        new_node->prev = NULL;
        return ;
    }
    last = *stack;
    while (last->next)
        last = last->next;
    last->next = new_node;
    new_node->prev = last;
}

static void	check_digits(char *str)
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

void	parsing_argv(int argc, char **argv, t_node **stack_a)
{
	char	**strs;
	int		val;
	int		i;
	int		j;

	i = 1;
	while (i < argc)
	{
		strs = ft_split(argv[i], ' ');
		j = 0;
		while(strs[j])
		{
			if(check_digits(strs[i]))
				exit_with_error(stack_a, strs);
			val = ft_atoi(strs[i]);
			if (val == INT_MAX || val == INT_MIN)
				exit_with_error(stack_a, strs);
			if (check_duplicates(*stack_a, val))
				exit_with_error(stack_a, strs);
			add_node_back(stack_a, val);
			j++;
		}
		i++;
	}
}
