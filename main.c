#include "push_swap.h"

int main(int argc, char **argv)
{
	char *str = argv[1];
	(void)argc;
	check_degit(str);
	char **strs= ft_split(str, ' ');
	int a = 0;
	int i = 0;

	while (strs[i])
	{
		a = ft_atoi(strs[i]);
		printf("%d\n", a);
		i++;
	}
}
