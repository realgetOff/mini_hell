/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 21:51:46 by pmilner-          #+#    #+#             */
/*   Updated: 2025/04/27 18:01:12 by mforest-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

int	is_whitespace(char c)
{
	if (c > 0 && c <= 32)
		return (1);
	return (0);
}

void	increment_until_next_c(char *line, int *i, char c)
{
	int	j;

	j = *i + 1;
	while (line[j] && line[j] != c)
		j++;
	if (line[j] != c)
		return ;
	*i = j;
}

int	lettercount_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (is_whitespace(line[i]))
			break ;
		if ((line[i] == '"' || line[i] == '\'') && line[i + 1])
			increment_until_next_c(line, &i, line[i]);
		i++;
	}
	return (i);
}

int	argcount(char *line)
{
	int	args;
	int	i;

	args = 0;
	i = 0;
	if (!is_whitespace(line[0]) && line[0])
		args++;
	while (line[i] && line[i + 1])
	{
		if ((line[i] == '"' || line[i] == '\'') && line[i + 1])
			increment_until_next_c(line, &i, line[i]);
		if (!is_whitespace(line[i]) && is_whitespace(line[i + 1]))
			args++;
		i++;
	}
	return (args);
}

char	**create_str_array(char *line)
{
	char	**str_array;
	int		i;
	int		j;

	str_array = (char **)malloc(sizeof(char *) * (argcount(line) + 1));
	if (!str_array)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (lettercount_line(&line[i]) && line[i])
		{
			str_array[j] = (char *)malloc(sizeof(char)
					* (lettercount_line(&line[i]) + 2));
			if (!str_array[j])
				return (NULL);
			j++;
			i += lettercount_line(&line[i]);
		}
		else
			i++;
	}
	return (str_array);
}
