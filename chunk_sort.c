/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaaz <hlaaz@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:02:01 by hlaaz             #+#    #+#             */
/*   Updated: 2026/01/05 11:40:12 by hlaaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_to_b(t_node **a, t_node **b, int size)
{
	int	i;
	int	range;

	i = 0;
	if (size <= 100)
		range = 15;
	else
		range = 33;
	while (*a)
	{
		if ((*a)->index <= i)
		{
			pb(a, b);
			rb(b);
			i++;
		}
		else if ((*a)->index <= i + range)
		{
			pb(a, b);
			i++;
		}
		else
			ra(a);
	}
}

void	push_to_a(t_node **a, t_node **b)
{
	t_node	*max;
	int		pos;
	int		size;

	while (*b)
	{
		size = ft_lstsize(*b);
		max = get_max_node(*b);
		pos = get_pos(*b, max);
		if (pos <= size / 2)
		{
			while (*b != max)
				rb(b);
		}
		else
		{
			while (*b != max)
				rrb(b);
		}
		pa(a, b);
	}
}
