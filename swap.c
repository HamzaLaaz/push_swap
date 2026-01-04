/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaaz <hlaaz@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 15:09:30 by hlaaz             #+#    #+#             */
/*   Updated: 2026/01/04 10:18:32 by hlaaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap(t_node **stack, int i)
{
	t_node	*first;
	t_node	*second;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	first = *stack;
	second = first->next;
	first->next = second->next;
	if (second->next)
		second->next->prev = first;
	second->next = first;
	second->prev = NULL;
	first->prev = second;
	*stack = second;
	if (i == 1)
		write(1, "sa\n", 3);
	else if (i == 2)
		write(1, "sb\n", 3);
}

void	sa(t_node **a)
{
	swap(a, 1);
}

void	sb(t_node **b)
{
	swap(b, 2);
}

void	ss(t_node **a, t_node **b)
{
	swap(a, 3);
	swap(b, 3);
	write(1, "ss\n", 3);
}
