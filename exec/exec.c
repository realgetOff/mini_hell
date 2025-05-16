/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:15:16 by pmilner-          #+#    #+#             */
/*   Updated: 2025/04/29 00:55:02 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

void	exec_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	ft_exec(t_node *node, t_exec *exec)
{
	char	*command_path;
	int		pid;
	int		exit_code;

	pid = fork();
	if (!pid)
	{
		if (execbuiltins(node, exec))
		{
			exit_code = exec->data->exit_code;
			ft_free(exec->data);
			destroy_exec(exec);
			exit(exit_code);
		}
		close_useless_fds(&node->io_fds, exec->pipefds, exec);
		close(exec->saved_out);
		command_path = command_verif(&node->io_fds, exec, node->cmd[0]);
		dup2_and_close(node->io_fds.in, 0);
		dup2_and_close(node->io_fds.out, 1);
		exec_signal();
		execve(command_path, node->cmd, exec->envp);
		if (command_path)
			free(command_path);
		exit_with_error(exec, errno, node->cmd[0]);
	}
}

void	full_exec(t_node *node, t_exec *exec)
{
	if (exec->cmd_count == 1)
	{
		if (!execbuiltins(node, exec))
			ft_exec(node, exec);
	}
	else
		ft_exec(node, exec);
}

void	exec_nodes(t_node *node, t_exec *exec, int layer)
{
	if (!node)
		return ;
	exec_nodes(node->left, exec, layer - 1);
	exec_nodes(node->right, exec, layer);
	if (node->cmd && node->cmd[0])
	{
		if (node->cmd[0][0] == '.' && !node->cmd[0][1])
		{
			ft_printf_err("mini_hell: .: filename argument required\n");
			ft_printf_err(".: usage: . filename [arguments]\n");
			exec->data->exit_code = 2;
			return ;
		}
		handle_override(node, exec->pipefds, layer, exec->cmd_count);
		full_exec(node, exec);
		close_after_use(&exec->pipefds[(layer + 1) % 2][0]);
		close_after_use(&exec->pipefds[(layer + 1) % 2][1]);
		if (layer < exec->cmd_count)
			pipe(exec->pipefds[(layer + 1) % 2]);
	}
	else if (node->io_fds.in == -1 || node->io_fds.out == -1)
		exec->data->exit_code = 1;
}

void	exec_cmds(t_data *data, t_read *entry)
{
	t_exec	exec;

	exec = init_exec(entry, data);
	if (exec.tokens)
	{
		exec_nodes(exec.first, &exec, exec.cmd_count);
		wait_loop(&exec);
		destroy_exec(&exec);
	}
}
