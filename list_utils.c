/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaaz <hlaaz@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 10:57:17 by hlaaz             #+#    #+#             */
/*   Updated: 2026/01/01 17:03:04 by hlaaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	add_node_back(t_node **stack, int value)
{
	t_node *new_node;
	t_node *last;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return ;
	new_node->value = value;
	new_node->next = NULL;
	if (*stack == NULL)
	{
		*stack = new_node;
		new_node->prev = NULL;
		return ;
	}
	last = *stack;
	while (last->next)
		last = last->next;
	last->next = new_node;
	new_node->prev = last;
}

int	ft_lstsize(t_list *lst)
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
