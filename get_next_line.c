/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaaz <hlaaz@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 11:59:08 by hlaaz             #+#    #+#             */
/*   Updated: 2026/01/05 11:59:41 by hlaaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

static char	*the_remainder(char *stach)
{
	char	*rmd;
	size_t	i;
	size_t	j;

	i = 0;
	if (!stach)
		return (NULL);
	while (stach[i] && stach[i] != '\n')
		i++;
	if (!stach[i])
		return (free(stach), NULL);
	i++;
	rmd = malloc(ft_strlen(stach) - i + 1);
	if (!rmd)
		return (free(stach), NULL);
	j = 0;
	while (stach[i])
		rmd[j++] = stach[i++];
	rmd[j] = '\0';
	free(stach);
	return (rmd);
}

static char	*creat_line(char *stach)
{
	char	*line;
	size_t	i;

	if (!stach)
		return (NULL);
	i = 0;
	while (stach[i] && stach[i] != '\n')
		i++;
	if (stach[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (stach[i] && stach[i] != '\n')
	{
		line[i] = stach[i];
		i++;
	}
	if (stach[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*creat_stach(int fd, char *buffer, char *stach)
{
	ssize_t	bytes;

	if (!buffer)
		return (NULL);
	bytes = 1;
	while (bytes != 0 && !ft_strchr(stach, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (free(buffer), free(stach), NULL);
		buffer[bytes] = '\0';
		stach = ft_strjoin(stach, buffer);
		if (!stach)
			return (free(buffer), NULL);
	}
	free(buffer);
	return (stach);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*stach;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	stach = creat_stach(fd, buffer, stach);
	if (!stach)
		return (NULL);
	if (!*stach)
		return (free(stach), stach = NULL, NULL);
	line = creat_line(stach);
	if (!line)
		return (free(stach), stach = NULL, NULL);
	stach = the_remainder(stach);
	return (line);
}
