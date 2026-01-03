/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaaz <hlaaz@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 12:03:59 by hlaaz             #+#    #+#             */
/*   Updated: 2026/01/03 12:06:25 by hlaaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"\

int	check_if_sorte(t_node *stack)
{
	while (stack && stack->next)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}
