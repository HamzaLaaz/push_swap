/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaaz <hlaaz@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 10:37:49 by hlaaz             #+#    #+#             */
/*   Updated: 2026/01/01 17:02:57 by hlaaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h> //!remove whene you whant to push
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_node
{
	int				value;
	int				index;
	struct s_node	*next;
	struct s_node	*prev;
}		t_node;

char	**ft_split(char *s, char c);
void	free_split(char **strs);
long	ft_atol(const char *str);
void	exit_error();
// void	check_digits(char *str);
void	parsing_argv(int argc, char **argv, t_node **stack_a);
void	exit_with_error(t_node **stack, char **strs);
void	free_stack(t_node **stack);
int		ft_lstsize(t_list *lst);
void 	add_node_back(t_node **stack, int value);
void	ra_and_rb(t_node **stack, int i);
void	rr(t_node **stack_a, t_node **stack_b);

#endif
