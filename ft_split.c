/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaaz <hlaaz@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 22:41:01 by hlaaz             #+#    #+#             */
/*   Updated: 2025/12/28 21:05:02 by hlaaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

static char	*creat_word(char **s, char c)
{
	char	*str;
	char	*ptr;
	int		i;
	int		j;

	while (**s && **s == c)
		(*s)++;
	ptr = *s;
	i = 0;
	while (ptr[i] && ptr[i] != c)
		i++;
	str = malloc(i +1);
	if (!str)
		return (NULL);
	j = 0;
	while (j < i)
	{
		str[j] = ptr[j];
		j++;
	}
	str [j] = '\0';
	*s += i;
	return (str);
}

static void	free_words(char **strs, int i)
{
	while (i >= 0)
	{
		free(strs[i]);
		i--;
	}
	free(strs);
}

char	**ft_split(char *s, char c)
{
	char	**strs;
	int		count;
	int		i;

	if (!s)
		return (NULL);
	count = count_words(s, c);
	strs = malloc(sizeof(char *) * (count + 1));
	if (!strs)
		return (NULL);
	i = 0;
	while (i < count)
	{
		strs[i] = creat_word(&s, c);
		if (!strs[i])
		{
			free_words(strs, i - 1);
			return (NULL);
		}
		i++;
	}
	strs[i] = NULL;
	return (strs);
}
