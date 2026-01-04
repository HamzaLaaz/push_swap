/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaaz <hlaaz@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 10:09:50 by hlaaz             #+#    #+#             */
/*   Updated: 2026/01/04 14:52:38 by hlaaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	sort(t_node **stack_a, t_node **stack_b, int size)
{
	if (size == 2)
		sa(stack_a);
	else if (size == 3)
		sort_three(stack_a);
	else if (size == 4)
		sort_four(stack_a, stack_b);
	else if (size == 5)
		sort_five(stack_a, stack_b);
	else
	{
		assign_index(stack_a);
		push_to_b(stack_a, stack_b, size);
		push_to_a(stack_a, stack_b);
	}
}

int	main(int argc, char **argv)
{
	t_node	*stack_a;
	t_node	*stack_b;
	int		size_s;

	stack_a = NULL;
	stack_b = NULL;
	if (argc == 1 || (argc == 2 && !argv[1][0]))
		return (0);
	parsing_argv(argc, argv, &stack_a);
	if (check_if_sorte(stack_a))
	{
		free_stack(&stack_a);
		return (0);
	}
	size_s = ft_lstsize(stack_a);
	sort(&stack_a, &stack_b, size_s);
	free_stack(&stack_a);
	free_stack(&stack_b);
	return (0);
}
