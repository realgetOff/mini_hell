/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:42:59 by pmilner-          #+#    #+#             */
/*   Updated: 2025/04/28 03:50:41 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

int	is_operator(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

static int	count_operator_splits(char *arg, int *i)
{
	int	count;

	count = 0;
	while (arg[*i] && is_operator(arg[*i]))
	{
		(*i)++;
		count++;
		if (arg[*i] && is_operator(arg[*i]) && arg[*i] != arg[(*i) - 1])
			break ;
	}
	return (count);
}

static int	count_normal_splits(char *arg, int *i)
{
	int		count;
	char	c;

	count = 0;
	while (arg[*i] && !is_operator(arg[*i]))
	{
		if ((arg[*i] == '\'' || arg[*i] == '"'))
		{
			if (!ft_strchr(&arg[*i + 1], arg[*i]))
				(*i)++;
			else
			{
				c = arg[*i];
				(*i)++;
				while (arg[*i] && arg[*i] != c)
					(*i)++;
				if (arg[*i])
					(*i)++;
			}
		}
		else
			(*i)++;
		count++;
	}
	return (count);
}

int	count_sub_splits(char *arg)
{
	int	i;
	int	count;

	if (!arg)
		return (0);
	i = 0;
	count = 0;
	if (!is_operator(arg[0]))
		count = 1;
	while (arg[i])
	{
		if (is_operator(arg[i]))
			count += count_operator_splits(arg, &i);
		else
			count += count_normal_splits(arg, &i);
	}
	return (count);
}

char	**split_tokens(char **line)
{
	char	**new_split;
	int		size;

	size = get_arg_count(line);
	new_split = (char **)ft_calloc(size + 1, sizeof(char *));
	if (!new_split)
		return (NULL);
	fill_split(new_split, line);
	return (new_split);
}
