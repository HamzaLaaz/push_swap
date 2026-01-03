/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaaz <hlaaz@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 10:57:17 by hlaaz             #+#    #+#             */
/*   Updated: 2026/01/03 10:32:03 by hlaaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	add_node_back(t_node **stack, int value)
{
	t_node *new;
	t_node *last;

	new = malloc(sizeof(t_node));
	if (!new)
		return ;
	new->value = value;
	new->next = NULL;
	if (*stack == NULL)
	{
		*stack = new;
		new->prev = NULL;
		return ;
	}
	last = *stack;
	while (last->next)
		last = last->next;
	last->next = new;
	new->prev = last;
}

int	ft_lstsize(t_node *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}
