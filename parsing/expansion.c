/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 01:21:03 by pmilner-          #+#    #+#             */
/*   Updated: 2025/04/27 18:03:57 by mforest-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

static int	calculate_total_size(char **split)
{
	int	size;
	int	i;

	i = 0;
	size = 0;
	while (split[i])
	{
		if (split[i][0] == '$' && split[i + 1] && i == 0)
			i++;
		if (split[i])
			size += ft_strlen(split[i++]);
	}
	return (size);
}

static char	*concatenate_strings(char **split, char *ret)
{
	int	i;

	i = 0;
	while (split[i])
	{
		if (split[i][0] == '$' && split[i + 1] && i == 0)
			i++;
		if (split[i])
			ret = ft_strcat(ret, split[i++]);
	}
	return (ret);
}

char	*join_arg(char **split)
{
	char	*ret;
	int		size;

	size = calculate_total_size(split);
	ret = (char *)ft_calloc(size + 1, sizeof(char));
	if (!ret)
		return (NULL);
	ret[0] = '\0';
	return (concatenate_strings(split, ret));
}

void	replace_dollars(char **split, t_read *entry, t_data *data)
{
	int	i;

	i = 0;
	while (split[i])
	{
		if (split[i][0] == '$')
			replace_dollar(&split[i], entry, data);
		i++;
	}
}

char	*expansion(t_read *entry, char *line, t_data *data)
{
	char	**quote_split;
	char	**tmp;
	int		i;

	i = 0;
	quote_split = split_quotes(line);
	while (quote_split[i])
	{
		if (quote_split[i][0] != '\'' && find_dollars(quote_split[i]))
		{
			tmp = split_dollars(quote_split[i]);
			replace_dollars(tmp, entry, data);
			free(quote_split[i]);
			quote_split[i] = join_arg(tmp);
			free_str_array(tmp);
		}
		i++;
	}
	free(line);
	line = join_arg(quote_split);
	free_str_array(quote_split);
	return (line);
}
