/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaaz <hlaaz@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 11:55:30 by hlaaz             #+#    #+#             */
/*   Updated: 2026/01/01 15:36:45 by hlaaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ra_and_rb(t_node **stack, int i)
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

void	rr(t_node **stack_a, t_node **stack_b)
{
	ra_and_rb(stack_a, 3);
	ra_and_rb(stack_b, 3);
	write(1, "rr\n", 3);
}
