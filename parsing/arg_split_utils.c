/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_split_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mforest- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:34:21 by mforest-          #+#    #+#             */
/*   Updated: 2025/04/27 17:01:06 by mforest-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

void	copy_arguement(char *dest, char *line, int *i)
{
	int	j;
	int	target;

	target = lettercount_line(&line[*i]);
	j = 0;
	while (j < target && line[*i])
	{
		dest[j] = line[*i];
		j++;
		(*i)++;
	}
	dest[j] = '\0';
}

char	**split_line(char *line)
{
	char	**str_array;
	int		i;
	int		k;

	i = 0;
	while (line[i] && is_whitespace(line[i]))
		i++;
	str_array = create_str_array(&line[i]);
	k = 0;
	while (line[i])
	{
		if (is_whitespace(line[i]))
			i++;
		else
			copy_arguement(str_array[k++], line, &i);
	}
	str_array[k] = NULL;
	return (str_array);
}
