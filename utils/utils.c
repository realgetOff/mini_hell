/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:00:00 by mforest-          #+#    #+#             */
/*   Updated: 2025/04/28 03:41:17 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

void	initialise_ijk(int *i, int *j, int *k)
{
	*i = 0;
	*j = 0;
	*k = 0;
}

void	free_str_array(char **str_array)
{
	int	i;

	i = 0;
	while (str_array[i])
		free(str_array[i++]);
	free(str_array);
}

void	exit_errorcode(t_data *data, int exit_code)
{
	ft_printf_err("exit\n");
	if (data)
		ft_free(data);
	exit(exit_code);
}

void	expand_all_args(t_arguements *argst, t_data *data)
{
	int	i;

	i = 0;
	while (argst[i].arg)
	{
		argst[i].arg = expansion(data->s_read, argst[i].arg, data);
		i++;
	}
}

void	remove_all_quotes(t_arguements *argst)
{
	int		i;
	char	*tmp;

	i = 0;
	while (argst[i].arg)
	{
		tmp = strip_quotes(argst[i].arg);
		free(argst[i].arg);
		argst[i].arg = tmp;
		i++;
	}
}
