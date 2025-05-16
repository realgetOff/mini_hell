/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils_two.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mforest- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:30:07 by mforest-          #+#    #+#             */
/*   Updated: 2025/04/27 18:04:11 by mforest-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

char	*join_quotes(char **quote_split)
{
	int		size;
	int		i;
	char	*ret;

	i = 0;
	size = 0;
	while (quote_split[i])
		size += ft_strlen(quote_split[i++]);
	ret = (char *)ft_calloc(size + 1, sizeof(char));
	if (!ret)
		return (NULL);
	ret[0] = '\0';
	i = 0;
	while (quote_split[i])
		ret = ft_strcat(ret, quote_split[i++]);
	return (ret);
}

void	process_dollar_split(char **ret, char *arg, t_dollar_indices *idx)
{
	if (arg[idx->i] == '$' && arg[idx->i + 1] == '$')
		idx->i++;
	else if (arg[idx->i] == '$')
	{
		ret[idx->k] = (char *)ft_calloc(idx->j + 1, sizeof(char));
		if (!ret[idx->k])
			return ;
		idx->k++;
		handle_dollar(ret, arg, &idx->i, &idx->k);
	}
	else
	{
		idx->i++;
		idx->j++;
	}
}

void	process_split_dollars(char **ret, char *arg, t_dollar_indices *idx)
{
	if (arg[idx->i] == '$' && arg[idx->i + 1] == '$')
		idx->i++;
	else if (arg[idx->i] == '$')
		copy_variable(ret, arg, &idx->i, &idx->k);
	else
	{
		idx->j = 0;
		while (arg[idx->i] && arg[idx->i] != '$')
			ret[idx->k][idx->j++] = arg[idx->i++];
	}
}

void	copy_variable(char **dest, char *src, int *i, int *k)
{
	int	j;

	(*k)++;
	j = 0;
	dest[*k][j++] = src[*i];
	(*i)++;
	if (src[*i] == '?')
	{
		dest[*k][j] = src[*i];
		(*i)++;
		j++;
	}
	else
	{
		while (src[*i] && ft_isvalid(src[*i]))
		{
			dest[*k][j] = src[*i];
			(*i)++;
			j++;
		}
	}
	(*k)++;
}

void	replace_dollar(char **src, t_read *entry, t_data *data)
{
	char	*var_name;
	char	*str;

	str = *src;
	if (str[1] == '?')
	{
		free(*src);
		*src = ft_itoa(data->exit_code);
		return ;
	}
	else if (!ft_isvalid(str[1]))
		return ;
	var_name = (char *)ft_calloc(ft_strlen(str) + 3, sizeof(char));
	if (!var_name)
		return ;
	var_name = ft_strcat(var_name, &str[1]);
	var_name = ft_strcat(var_name, "=");
	free(*src);
	*src = get_var(entry, var_name);
	free(var_name);
	return ;
}
