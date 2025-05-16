/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split_fill.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:53:13 by mforest-          #+#    #+#             */
/*   Updated: 2025/04/28 03:50:55 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

static void	fill_operator(char *dest, char *src, int *i, int *j)
{
	while (src[*i] && is_operator(src[*i]))
	{
		dest[(*j)++] = src[(*i)++];
		if (is_operator(src[*i]) && src[*i] != src[(*i) - 1])
			break ;
	}
}

static void	fill_normal_str(char *dest, char *src, int *i, int *j)
{
	char	c;

	while (src[*i] && !is_operator(src[*i]))
	{
		if ((src[*i] == '\'' || src[*i] == '"'))
		{
			if (!ft_strchr(&src[*i + 1], src[*i]))
				dest[(*j)++] = src[(*i)++];
			else
			{
				c = src[*i];
				dest[(*j)++] = src[(*i)++];
				while (src[*i] && src[*i] != c)
					dest[(*j)++] = src[(*i)++];
				dest[(*j)++] = src[(*i)++];
			}
		}
		else
			dest[(*j)++] = src[(*i)++];
	}
}

void	fill_sub_str(char *dest, char *src, int *i)
{
	int	j;

	j = 0;
	if (is_operator(src[*i]))
		fill_operator(dest, src, i, &j);
	else
		fill_normal_str(dest, src, i, &j);
}

void	fill_split(char **dest, char **src)
{
	int	i;
	int	j;
	int	k;
	int	size;

	i = 0;
	k = 0;
	while (src[i])
	{
		j = 0;
		while (src[i][j])
		{
			size = get_size_tok(&src[i][j]);
			dest[k] = (char *)ft_calloc(size + 2, sizeof(char));
			if (!dest[k])
				return ;
			fill_sub_str(dest[k], src[i], &j);
			k++;
		}
		i++;
	}
}
