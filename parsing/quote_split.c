/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mforest- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 23:01:39 by mforest-          #+#    #+#             */
/*   Updated: 2025/04/27 18:01:59 by mforest-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Deal with dollars here
// need to store $? somewhere
// need to also fix the builtins.

#include "mini_hell.h"

static int	splitcount(char *line)
{
	int	args;
	int	i;

	args = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			increment_until_next_c(line, &i, line[i]);
			i++;
			args++;
		}
		else
		{
			while (line[i] != '"' && line[i] != '\'' && line[i])
				i++;
			args++;
		}
	}
	return (args);
}

char	*dup_quotes(char *src, char c)
{
	int		i;
	char	*ret;

	i = 1;
	while (src[i] && src[i] != c)
		i++;
	ret = (char *)ft_calloc(i + 3, sizeof(char));
	if (!ret)
		return (NULL);
	i = 1;
	ret[0] = src[0];
	while (src[i] && src[i] != c)
	{
		ret[i] = src[i];
		i++;
	}
	ret[i] = src[i];
	return (ret);
}

char	*dup_until_quotes(char *src)
{
	int		i;
	char	*ret;

	i = 0;
	while (src[i] && src[i] != '"' && src[i] != '\'')
		i++;
	ret = (char *)ft_calloc(sizeof(char), i + 1);
	if (!ret)
		return (NULL);
	i = 0;
	while (src[i] && src[i] != '"' && src[i] != '\'')
	{
		ret[i] = src[i];
		i++;
	}
	return (ret);
}

char	**split_quotes(char *line)
{
	int		i;
	int		j;
	char	**ret;

	i = 0;
	j = 0;
	ret = (char **)ft_calloc((splitcount(line) + 1), sizeof(char *));
	if (!ret)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			ret[j] = dup_quotes(&line[i], line[i]);
			i += subquote_count(&line[i + 1], line[i]) + 2;
		}
		else
		{
			ret[j] = dup_until_quotes(&line[i]);
			while (line[i] && line[i] != '"' && line[i] != '\'')
				i++;
		}
		j++;
	}
	return (ret);
}
