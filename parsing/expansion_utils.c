/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 23:11:39 by mforest-          #+#    #+#             */
/*   Updated: 2025/04/28 03:38:20 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

char	**split_dollars(char *arg)
{
	t_dollar_indices	idx;
	char				**ret;

	ret = create_dollar_split(arg);
	if (!ret)
		return (NULL);
	initialise_ijk(&idx.i, &idx.j, &idx.k);
	while (arg[idx.i])
		process_split_dollars(ret, arg, &idx);
	return (ret);
}

int	ft_isvalid(int c)
{
	if (c != '_')
		if (c < 'a' || c > 'z')
			if (c < 'A' || c > 'Z')
				if (c < '0' || c > '9')
					return (0);
	return (1);
}

int	find_dollars(char *arg)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (arg[i])
	{
		if (arg[i] == '$')
		{
			count++;
			if (arg[i + 1] == '$')
				i++;
		}
		i++;
	}
	return (count);
}

char	**create_dollar_split(char *arg)
{
	t_dollar_indices	idx;
	char				**ret;

	ret = (char **)ft_calloc(find_dollars(arg) * 2 + 4, sizeof(char *));
	if (!ret)
		return (NULL);
	initialise_ijk(&idx.i, &idx.j, &idx.k);
	while (arg[idx.i])
		process_dollar_split(ret, arg, &idx);
	if (idx.j > 0)
	{
		ret[idx.k] = (char *)ft_calloc(idx.j + 1, sizeof(char));
		if (!ret[idx.k])
			return (NULL);
	}
	return (ret);
}

void	handle_dollar(char **ret, char *arg, int *i, int *k)
{
	int	j;

	j = 0;
	(*i)++;
	while (arg[*i] && ft_isvalid(arg[*i]))
	{
		j++;
		(*i)++;
	}
	ret[(*k)] = (char *)ft_calloc(j + 2, sizeof(char));
	if (!ret[*k])
		return ;
	(*k)++;
}
