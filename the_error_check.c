/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_error_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaaz <hlaaz@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 11:51:05 by hlaaz             #+#    #+#             */
/*   Updated: 2025/12/31 11:53:23 by hlaaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_stack(t_node **stack)
{
	t_node	*tmp;
	t_node	*curr;

	if (!stack || !*stack)
		return ;
	curr = *stack;
	while (curr)
	{
		tmp = curr->next;
		free(curr);
		curr = tmp;
	}
	*stack = NULL;
}

void	exit_with_error(t_node **stack, char **strs)
{
	free_stack(stack);

	write(2, "Error\n", 6);
	exit(1);
}
