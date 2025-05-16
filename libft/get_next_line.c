/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:10:34 by pmilner-          #+#    #+#             */
/*   Updated: 2024/11/07 02:44:09 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_nl(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	i += (!str[i] || str[i] == '\n');
	return (i);
}

static int	fillstash(char **stash, int fd)
{
	char	*buffer;
	int		temp;
	char	*strtmp;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	while (!ft_strchr(*stash, '\n'))
	{
		temp = read(fd, buffer, BUFFER_SIZE);
		if (temp < 0)
		{
			free(buffer);
			return (0);
		}
		if (temp == 0)
			break ;
		buffer[temp] = '\0';
		strtmp = *stash;
		*stash = ft_strjoin(*stash, buffer);
		free(strtmp);
		strtmp = NULL;
	}
	free(buffer);
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*newline;
	int			temp;
	char		*strtmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return (NULL);
	if (!stash)
		stash = ft_strdup("");
	if (!fillstash(&stash, fd))
		return (NULL);
	temp = find_nl(stash);
	newline = ft_substr(stash, 0, temp);
	strtmp = stash;
	stash = ft_substr(stash, temp, BUFFER_SIZE);
	free(strtmp);
	strtmp = NULL;
	return (newline);
}
