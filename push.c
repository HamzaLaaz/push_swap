/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaaz <hlaaz@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 17:42:08 by hlaaz             #+#    #+#             */
/*   Updated: 2026/01/05 14:29:34 by hlaaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	push(t_node **src, t_node **dest, int i)
{
	t_node	*push;

	if (!src || !*src)
		return ;
	push = *src;
	*src = push->next;
	if (*src)
		(*src)->prev = NULL;
	push->next = *dest;
	if (*dest)
		(*dest)->prev = push;
	*dest = push;
	push->prev = NULL;
	if (i == 1)
		write(1, "pa\n", 3);
	else if (i == 2)
		write(1, "pb\n", 3);
}

void	pa(t_node **a, t_node **b, int i)
{
	push(b, a, i);
}

void	pb(t_node **a, t_node **b, int i)
{
	push(a, b, i);
}
