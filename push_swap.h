/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaaz <hlaaz@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 10:37:49 by hlaaz             #+#    #+#             */
/*   Updated: 2026/01/03 15:30:56 by hlaaz            ###   ########.fr       */
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
int		ft_lstsize(t_node *lst);
void 	add_node_back(t_node **stack, int value);

int	check_if_sorte(t_node *stack);
void	sort_three(t_node **stack);

void	sa(t_node **a);
void	sb(t_node **b);
void	ss(t_node **a, t_node **b);

void	ra(t_node **a);
void	rb(t_node **b);
void	rr(t_node **a, t_node **b);

void	rra(t_node **a);
void	rra(t_node **b);
void	rrr(t_node **a, t_node **b);

void	pa(t_node **a, t_node **b);
void	pb(t_node **a, t_node **b);

#endif
