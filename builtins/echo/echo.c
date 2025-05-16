/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 04:00:10 by mforest-          #+#    #+#             */
/*   Updated: 2025/04/06 17:11:17 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

static void	check_args(char **args, int *i, int *opt_n)
{
	int	j;

	*opt_n = 0;
	while (args[*i] && args[*i][0] == '-')
	{
		j = 1;
		while (args[*i][j] && args[*i][j] == 'n')
			j++;
		if (args[*i][j])
			break ;
		*opt_n = 1;
		(*i)++;
	}
}

void	ft_echo(t_exec *exec, t_node *node)
{
	int		i;
	int		opt_n;
	char	**args;

	args = node->cmd;
	i = 1;
	check_args(args, &i, &opt_n);
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1] && args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (opt_n == 0)
		write(1, "\n", 1);
	exec->data->exit_code = 0;
}
