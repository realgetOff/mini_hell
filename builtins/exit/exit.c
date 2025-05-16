/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 21:33:28 by mforest-          #+#    #+#             */
/*   Updated: 2025/04/28 22:03:46 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"
#include <limits.h>

static int	almost_atoi(char *str, int *err)
{
	unsigned long long	ret;
	int					i;
	int					j;
	int					pn;

	i = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	pn = 1;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			pn = -1;
	j = i;
	ret = 0;
	while ('0' <= str[i] && str[i] <= '9')
		ret = ret * 10 + (str[i++] - 48);
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] || i - j > 20 || ((pn == -1 && (ret - 1) > LONG_MAX) || (pn == 1
				&& (ret > LONG_MAX))))
		*err = 1;
	return ((int)((ret * pn) % 256));
}

static int	check_args(t_data *data, char **cmd)
{
	int	exit_value;
	int	error;

	error = 0;
	exit_value = almost_atoi(cmd[1], &error);
	if (error)
	{
		ft_printf_err("exit: %s: numeric argument required\n", cmd[1]);
		data->exit_code = 2;
		return (0);
	}
	if (cmd[2])
	{
		ft_printf_err("exit: too many arguments\n");
		data->exit_code = 1;
		return (1);
	}
	data->exit_code = exit_value;
	return (0);
}

void	ft_exit(t_exec *exec, t_node *node)
{
	int	exit_code;

	ft_printf_err("exit\n");
	if (node->cmd[1])
		if (check_args(exec->data, node->cmd))
			return ;
	exit_code = exec->data->exit_code;
	ft_free(exec->data);
	dup2_and_close(0, node->io_fds.in);
	dup2_and_close(1, node->io_fds.out);
	destroy_exec(exec);
	exit(exit_code);
}
