#include "push_swap.h"

static void	sort(t_node **stack_a, t_node **stack_b, int size)
{
	if (size == 2)
		sa(&stack_a);
	else if (size == 3)
		sort_three(&stack_a);
	else if (size == 4)
		sort_four(&stack_a, &stack_b);
	else if (size == 5)
		sort_five(&stack_a, &stack_b);
	else if (size > 5)
		sort_big(&stack_a, &stack_b);
	free_stack(&stack_a);
	free_stack(&stack_b);
}
int	main(int argc, char **argv)
{
	t_node	*stack_a;
	t_node	*stack_b;
	int		size_s;

	stack_a = NULL;
	stack_b = NULL;
	if (argc == 1 || (argc == 2 && !argv[1][0]))
		return (0);
	else
		argv = argv + 1;
	parsing_argv(argc, argv, &stack_a);
	size_s = ft_lstsize(stack_a);
	sort(&stack_a, &stack_b, size_s);

}





	// t_node	*stack_a;
	// t_node	*stack_b;
	// // int		size_s;
	// t_node *head;

	// stack_a = NULL;
	// stack_b = NULL;
	// // if (argc == 1 || (argc == 2 && !argv[1][0]))
	// // 	return (1);
	// // else if (argc == 2)
	// // 	argv = ft_split(argv[1], ' ');
	// // else
	// 	// argv = argv + 1;
	// parsing_argv(argc, argv, &stack_a);
	// parsing_argv(argc, argv, &stack_b);
	// // size_s = ft_lstsiz(stack_a);
	// rr(&stack_a, &stack_b);
	// 	// parsing_argv(argc, argv, &stack_a);
	// head = stack_a;
	// while (head)
	// {
	// 	printf("%d\n", head->value);
	// 	head = head->next;
	// }
	// free_stack(&stack_a);
	// head = stack_b;
	// while (head)
	// {
	// 	printf("%d\n", head->value);
	// 	head = head->next;
	// }
	// free_stack(&stack_b);
