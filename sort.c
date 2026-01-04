/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaaz <hlaaz@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 12:13:01 by hlaaz             #+#    #+#             */
/*   Updated: 2026/01/04 15:09:59 by hlaaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*get_max_node(t_node *stack)
{
	t_node	*max_node;

	if (!stack)
		return (NULL);
	max_node = stack;
	while (stack)
	{
		if (stack->value > max_node->value)
			max_node = stack;
		stack = stack->next;
	}
	return (max_node);
}

static t_node	*get_min_node(t_node *stack)
{
	t_node	*min_node;

	if (!stack)
		return (NULL);
	min_node = stack;
	while (stack)
	{
		if (stack->value < min_node->value)
			min_node = stack;
		stack = stack->next;
	}
	return (min_node);
}

void	sort_three(t_node **stack)
{
	t_node	*max_node;

	max_node = get_max_node(*stack);
	if (*stack == max_node)
		ra(stack);
	else if ((*stack)->next == max_node)
		rra(stack);
	if ((*stack)->value > (*stack)->next->value)
		sa(stack);
}

void	sort_four(t_node **a, t_node **b)
{
	t_node	*min_node;

	min_node = get_min_node(*a);
	while (*a != min_node)
	{
		if (get_pos(*a, min_node) <= 2)
			ra(a);
		else
			rra(a);
	}
	pb(a, b);
	sort_three(a);
	pa(a, b);
}

void	sort_five(t_node **a, t_node **b)
{
	t_node	*min_node;

	min_node = get_min_node(*a);
	while (*a != min_node)
	{
		if (get_pos(*a, min_node) <= 2)
			ra(a);
		else
			rra(a);
	}
	pb(a, b);
	min_node = get_min_node(*a);
	while (*a != min_node)
	{
		if (get_pos(*a, min_node) <= 1)
			ra(a);
		else
			rra(a);
	}
	pb(a, b);
	sort_three(a);
	pa(a, b);
	pa(a, b);
}
