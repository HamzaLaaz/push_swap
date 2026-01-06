/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rrotate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaaz <hlaaz@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 17:40:24 by hlaaz             #+#    #+#             */
/*   Updated: 2026/01/06 09:54:28 by hlaaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rrotate(t_node **stack, int i)
{
	t_node	*first;
	t_node	*last;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	first = *stack;
	last = *stack;
	while (last->next)
		last = last->next;
	if (last->prev)
		last->prev->next = NULL;
	last->next = first;
	last->prev = NULL;
	first->prev = last;
	*stack = last;
	if (i == 1)
		write(1, "rra\n", 4);
	else if (i == 2)
		write(1, "rrb\n", 4);
	else
		return ;
}

void	rra(t_node **a, int i)
{
	if (i == 1)
		rrotate(a, 1);
	else
		rrotate(a, 3);
}

void	rrb(t_node **b, int i)
{
	if (i == 2)
		rrotate(b, 2);
	else
		rrotate(b, 3);
}

void	rrr(t_node **a, t_node **b, int i)
{
	rrotate(a, 3);
	rrotate(b, 3);
	if (i == 4)
		write(1, "rrr\n", 4);
}
