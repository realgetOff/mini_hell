/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_six.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mforest- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 22:53:39 by mforest-          #+#    #+#             */
/*   Updated: 2025/04/26 22:58:59 by mforest-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

static char	**alloc_operator(char **out, int *i, int *k, char *in)
{
	if (in[*i] && in[*i] == '+')
		(*i)++;
	if (in[*i] && in[*i] == '=')
		(*i)++;
	out[*k] = (char *)ft_calloc(*i + 1, sizeof(char));
	if (!out[*k])
		return (NULL);
	if (!in[*i])
		return (out);
	(*k)++;
	return (out);
}

static char	**alloc_value(char **out, int *i, int *k, char *in)
{
	while (in[*i])
		(*i)++;
	out[*k] = (char *)ft_calloc(*i + 1, sizeof(char));
	if (!out[*k])
		return (NULL);
	return (out);
}

char	**alloc_split_next(char **out, int *i, int *k, char *in)
{
	out = alloc_operator(out, i, k, in);
	if (!out)
		return (NULL);
	out = alloc_value(out, i, k, in);
	if (!out)
		return (NULL);
	return (out);
}
