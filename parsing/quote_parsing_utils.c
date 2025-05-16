/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parsing_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mforest- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:15:07 by mforest-          #+#    #+#             */
/*   Updated: 2024/04/27 15:15:07 by mforest-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

void	strcpy_until_c(char *dest, char *src, char c)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != c)
	{
		dest[i] = src[i];
		i++;
	}
}

int	subquote_count(char *line, char c)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != c)
		i++;
	return (i);
}

int	getsize_stripped(char *line)
{
	int	i;
	int	size;
	int	tmp;

	i = 0;
	size = 0;
	while (line[i])
	{
		if ((line[i] == '"' || line[i] == '\'') && line[i + 1])
		{
			if (!ft_strchr(line, line[i]))
				size++;
			else
			{
				tmp = subquote_count(&line[i + 1], line[i]);
				size += tmp;
				i += tmp + 1;
			}
		}
		else
			size++;
		if (line[i])
			i++;
	}
	return (size);
}

void	process_quotes(char *ret, char *line, int *i, int *j)
{
	int	tmp;

	if ((line[*i] == '"' || line[*i] == '\'') && line[*i + 1])
	{
		strcpy_until_c(&ret[*j], &line[*i + 1], line[*i]);
		tmp = subquote_count(&line[*i + 1], line[*i]);
		*i += tmp + 2;
		*j += tmp;
	}
	else
	{
		ret[*j] = line[*i];
		(*i)++;
		(*j)++;
	}
}
