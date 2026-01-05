/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaaz <hlaaz@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 11:55:32 by hlaaz             #+#    #+#             */
/*   Updated: 2026/01/05 14:30:14 by hlaaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

static int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

static void	execute_operation(char *line, t_node **a, t_node **b)
{
	if (!line)
		return ;
	if (ft_strcmp(line, "sa\n") == 0)
		sa(a, 3);
	else if (ft_strcmp(line, "sb\n") == 0)
		sb(b, 3);
	else if (ft_strcmp(line, "ss\n") == 0)
		ss(a, b, 3);
	else if (ft_strcmp(line, "pa\n") == 0)
		pa(a, b, 3);
	else if (ft_strcmp(line, "pb\n") == 0)
		pb(a, b, 3);
	else if (ft_strcmp(line, "ra\n") == 0)
		ra(a, 3);
	else if (ft_strcmp(line, "rb\n") == 0)
		rb(b, 3);
	else if (ft_strcmp(line, "rr\n") == 0)
		rr(a, b, 3);
	else if (ft_strcmp(line, "rra\n") == 0)
		rra(a, 3);
	else if (ft_strcmp(line, "rrb\n") == 0)
		rrb(b, 3);
	else if (ft_strcmp(line, "rrr\n") == 0)
		rrr(a, b, 3);
	else
		exit_error();
}

static void	read_and_execute(t_node **a, t_node **b)
{
	char	*line;

	while (1)
	{
		line = get_next_line(0);
		if (!line)
			break ;
		execute_operation(line, a, b);
		free(line);
	}
}

int	main(int argc, char **argv)
{
	t_node	*stack_a;
	t_node	*stack_b;

	stack_a = NULL;
	stack_b = NULL;
	if (argc == 1 || (argc == 2 && !argv[1][0]))
		return (0);
	parsing_argv(argc, argv, &stack_a);
	read_and_execute(&stack_a, &stack_b);
	if (check_if_sorte(stack_a) && stack_b == NULL)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	free_stack(&stack_a);
	free_stack(&stack_b);
	return (0);
}
