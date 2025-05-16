/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:25:23 by pmilner-          #+#    #+#             */
/*   Updated: 2025/04/27 02:29:49 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

int	cmd_count(t_arguements *array)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (array[i].arg && array[i].type != TOKEN_OPERATOR)
	{
		if (array[i].type == TOKEN_ARGUEMENT || array[i].type == TOKEN_COMMAND
			|| array[i].type == TOKEN_ASSIGNMENT)
			count += argcount(array[i].arg);
		i++;
	}
	return (count);
}

void	fill_cmd_array(char *arg, int *j, char **ret)
{
	char	**tmp;
	int		i;

	tmp = split_line(arg);
	i = 0;
	while (tmp[i])
	{
		ret[*j] = strip_quotes(tmp[i]);
		i++;
		(*j)++;
	}
	free_str_array(tmp);
}

char	**create_cmd_array(t_arguements *array)
{
	int		size;
	int		i;
	int		j;
	char	**ret;

	size = cmd_count(array);
	ret = (char **)ft_calloc(size + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	while (array[i].arg && array[i].type != TOKEN_OPERATOR)
	{
		if (array[i].type == TOKEN_COMMAND || array[i].type == TOKEN_ARGUEMENT)
			fill_cmd_array(array[i].arg, &j, ret);
		else if (array[i].type == TOKEN_ASSIGNMENT)
			ret[j++] = strip_quotes(array[i].arg);
		if (array[i].arg)
			i++;
	}
	i = 0;
	return (ret);
}
