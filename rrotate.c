/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rrotate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaaz <hlaaz@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 17:40:24 by hlaaz             #+#    #+#             */
/*   Updated: 2026/01/03 10:35:30 by hlaaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rrotate(t_node **stack, int i)
{
	t_node	*first;
	t_node	*last;

	if (!*stack || !(*stack)->next)
		return ;
	first = *stack;
	last = *stack;
	while (last->next)
		last = last->next;
	last->prev->next = NULL;
	last->next = first;
	last->prev = NULL;
	first->prev = last;
	*stack = last;
	if (i == 1)
		write(1, "rra\n", 3);
	else if (i == 2)
		write(1, "rrb\n", 3);
	else
		return ;
}

void	rra(t_node **a)
{
	rrotate(a, 1);
}

void	rrb(t_node **b)
{
	rrotate(b, 2);
}

void	rrr(t_node **a, t_node **b)
{
	rrotate(a, 3);
	rrotate(b, 3);
	write(1, "rr\n", 3);
}
