#include "push_swap.h"

int main()
{
	char *str = "12 1 23  3 23 344  4 4 4 44 ";
	char **strs= ft_split(str, ' ');
	int i = 0;

	while (strs[i])
	{
		printf("%s\n", strs[i]);
		i++;
	}
}
