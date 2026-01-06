/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaaz <hlaaz@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 10:37:49 by hlaaz             #+#    #+#             */
/*   Updated: 2026/01/06 15:54:39 by hlaaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>

/* --- STACK STRUCTURE --- */
typedef struct s_node
{
	int				value;
	int				index;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

/* --- MANDATORY OPERATIONS --- */

// push.c
void	pa(t_node **a, t_node **b, int i);
void	pb(t_node **a, t_node **b, int i);

// swap.c
void	sa(t_node **a, int i);
void	sb(t_node **b, int i);
void	ss(t_node **a, t_node **b, int i);

// rotate.c
void	ra(t_node **a, int i);
void	rb(t_node **b, int i);
void	rr(t_node **a, t_node **b, int i);

// rrotate.c
void	rra(t_node **a, int i);
void	rrb(t_node **b, int i);
void	rrr(t_node **a, t_node **b, int i);

/* --- ALGORITHMS --- */

// sort.c
t_node	*get_max_node(t_node *stack);
void	sort_three(t_node **stack);
void	sort_four(t_node **a, t_node **b);
void	sort_five(t_node **a, t_node **b);

// chunk_sort.c
void	push_to_b(t_node **a, t_node **b, int size);
void	push_to_a(t_node **a, t_node **b);

// sort_utils.c
int		check_if_sorte(t_node *stack);
void	assign_index(t_node **stack_a);
int		get_pos(t_node *stack, t_node *target);

/* --- PARSING & UTILS --- */

// parsing.c
void	parsing_argv(int argc, char **argv, t_node **stack_a);
char	**ft_split(char *s, char c);
long	ft_atol(const char *str);

// list_utils.c
void	add_node_back(t_node **stack, int value);
int		ft_lstsize(t_node *lst);

// error_free.c
void	free_stack(t_node **stack);
void	free_split(char **strs);
void	exit_error(void);
void	exit_with_error(t_node **stack, char **strs);
void	exit_free(t_node **a, t_node **b, char *line);

#endif
