/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_five.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mforest- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 22:53:39 by mforest-          #+#    #+#             */
/*   Updated: 2025/04/27 16:50:13 by mforest-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

static int	find_operator(char *in, int *i)
{
	while (in[*i] && (ft_strncmp(&in[*i], "+=", 2) && in[*i] != '='))
		(*i)++;
	return (*i);
}

static char	**alloc_name(char **out, char *in, t_indices *idx)
{
	out[idx->k] = (char *)ft_calloc(idx->i + 1, sizeof(char));
	if (!out[idx->k])
		return (NULL);
	if (!in[idx->i])
	{
		free(out[idx->k]);
		out[idx->k] = NULL;
		return (out);
	}
	idx->k++;
	return (out);
}

static char	**alloc_operator(char **out, char *in, t_indices *idx)
{
	if (in[idx->i] && in[idx->i] == '+')
		idx->i++;
	if (in[idx->i] && in[idx->i] == '=')
		idx->i++;
	out[idx->k] = (char *)ft_calloc(idx->i + 1 - idx->j, sizeof(char));
	if (!out[idx->k])
		return (NULL);
	if (!in[idx->i])
	{
		free(out[idx->k]);
		out[idx->k] = NULL;
		return (out);
	}
	idx->k++;
	return (out);
}

static char	**alloc_value(char **out, char *in, t_indices *idx)
{
	while (in[idx->i])
		idx->i++;
	out[idx->k] = (char *)ft_calloc(idx->i + 1 - idx->j, sizeof(char));
	if (!out[idx->k])
		return (NULL);
	return (out);
}

char	**alloc_split(char *in)
{
	t_indices	idx;
	char		**out;

	idx.i = 0;
	idx.j = 0;
	idx.k = 0;
	out = (char **)ft_calloc(4, sizeof(char *));
	if (!out)
		return (NULL);
	find_operator(in, &idx.i);
	out = alloc_name(out, in, &idx);
	if (!out)
		return (NULL);
	out = alloc_operator(out, in, &idx);
	if (!out)
		return (NULL);
	out = alloc_value(out, in, &idx);
	if (!out)
		return (NULL);
	return (out);
}
