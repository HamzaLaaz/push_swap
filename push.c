/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaaz <hlaaz@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 17:42:08 by hlaaz             #+#    #+#             */
/*   Updated: 2026/01/01 17:53:22 by hlaaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push(t_node **src, t_node **dest, char *op)
{
	t_node *push;

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
	if (op)
		write(1, op, 3);
}
