/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaaz <hlaaz@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 10:37:49 by hlaaz             #+#    #+#             */
/*   Updated: 2025/12/28 23:06:49 by hlaaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h> //!remove whene you whant to push
# include <unistd.h>
# include <stdlib.h>

typedef struct s_stack
{
	int				value;
	int				index;
	int				cost;
	struct s_stack	*target_node;
	struct s_stack	*next;
	struct s_stack	*prev;
}		t_stack;

char	**ft_split(char *s, char c);

#endif
