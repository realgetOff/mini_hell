/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split_utils_two.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mforest- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:59:36 by mforest-          #+#    #+#             */
/*   Updated: 2025/04/27 17:59:49 by mforest-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

int	get_arg_count(char **line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		count += count_sub_splits(line[i]);
		i++;
	}
	return (count);
}

int	get_size_tok(char *src)
{
	int	i;

	i = 0;
	if (is_operator(src[0]))
	{
		while (src[i] && is_operator(src[i]))
		{
			i++;
			if (is_operator(src[i]) && src[i] != src[i - 1])
				return (i);
		}
		return (i);
	}
	while (src[i] && !is_operator(src[i]))
	{
		if ((src[i] == '\'' || src[i] == '"') && src[i + 1])
			increment_until_next_c(src, &i, src[i]);
		if (src[i])
			i++;
	}
	return (i);
}
