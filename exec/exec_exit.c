/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:31:14 by pmilner-          #+#    #+#             */
/*   Updated: 2025/04/27 02:18:22 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

void	wait_loop(t_exec *exec)
{
	int	child_pid;
	int	last_pid;
	int	status;

	last_pid = 0;
	status = 0;
	signal(SIGINT, SIG_IGN);
	while (exec->cmd_count)
	{
		child_pid = waitpid(0, &status, 0);
		if (WIFEXITED(status) || WIFSIGNALED(status))
		{
			if (last_pid < child_pid)
			{
				last_pid = child_pid;
				handle_exit_status(status, &exec->data->exit_code);
			}
		}
		exec->cmd_count--;
	}
	setup_signals(exec->data);
}
