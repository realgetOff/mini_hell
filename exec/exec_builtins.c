/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:15:16 by pmilner-          #+#    #+#             */
/*   Updated: 2025/04/28 02:05:55 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

static int	handle_builtin(t_node *node, t_exec *exec,
		const t_builtins *builtin)
{
	if (node->io_fds.in == -1 || node->io_fds.out == -1)
	{
		exec->data->exit_code = 1;
		return (1);
	}
	if (exec->saved_out != node->io_fds.out)
		close(exec->saved_out);
	if (node->io_fds.in > 2)
		close (node->io_fds.in);
	dup2_and_close(node->io_fds.out, STDOUT_FILENO);
	builtin->f(exec, node);
	dup2_and_close(exec->saved_out, STDOUT_FILENO);
	return (1);
}

int	execbuiltins(t_node *node, t_exec *exec)
{
	static const t_builtins	builtins[] = {{"cd", cd, 1}, {"env", env, 1},
	{"unset", unset, 0}, {"exit", ft_exit, 1}, {"echo", ft_echo, 0},
	{"pwd", pwd, 0}, {"export", ft_export, 0}, {NULL, NULL, 0}};
	int						i;

	i = 0;
	while (builtins[i].entry)
	{
		if (!ft_strcmp(node->cmd[0], builtins[i].entry)
			&& ft_strlen(builtins[i].entry) == ft_strlen(node->cmd[0]))
			return (handle_builtin(node, exec, &builtins[i]));
		i++;
	}
	return (0);
}
