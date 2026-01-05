/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaaz <hlaaz@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 11:55:30 by hlaaz             #+#    #+#             */
/*   Updated: 2026/01/05 14:33:32 by hlaaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rotate(t_node **stack, int i)
{
	t_node	*first;
	t_node	*second;
	t_node	*last;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	first = *stack;
	second = first->next;
	last = first;
	while (last->next)
		last = last->next;
	*stack = second;
	second->prev = NULL;
	last->next = first;
	first->prev = last;
	first->next = NULL;
	if (i == 1)
		write(1, "ra\n", 3);
	else if (i == 2)
		write(1, "rb\n", 3);
	else
		return ;
}

void	ra(t_node **a, int i)
{
	if (i == 1)
		rotate(a, 1);
	else
		rotate(a, 3);
}

void	rb(t_node **b, int i)
{
	if (i == 2)
		rotate(b, 2);
	else
		rotate(b, 3);
}

void	rr(t_node **a, t_node **b, int i)
{
	rotate(a, 3);
	rotate(b, 3);
	if (i == 4)
		write(1, "rr\n", 3);
}
