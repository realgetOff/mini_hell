/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:31:14 by pmilner-          #+#    #+#             */
/*   Updated: 2025/04/29 00:47:54 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

static int	translate_exit(int waitexit)
{
	if (waitexit == -2)
		return (2);
	else if (waitexit == ENOENT)
		return (127);
	else if (waitexit == EACCES)
		return (126);
	else if (waitexit == EXIT_FAILURE)
		return (1);
	return (waitexit);
}

void	exit_with_error(t_exec *exec, int errornum, char *command)
{
	ft_free(exec->data);
	if (errornum == ENOENT && !chr_present(command, '/'))
	{
		ft_printf_err("%s: command not found\n", command);
		destroy_exec(exec);
		exit(errornum);
	}
	else if (errornum != 1)
	{
		ft_printf_err("mini_hell: cmd: ");
		perror("");
		destroy_exec(exec);
		exit(errornum);
	}
	destroy_exec(exec);
	exit(errornum);
}

void	handle_exit_status(int status, int *exit_code)
{
	int	signal;

	if (status & 0x7F)
	{
		signal = status & 0x7F;
		get_signal_name(signal);
		print_signal(signal);
		*exit_code = signal + 128;
	}
	else
		*exit_code = translate_exit(WEXITSTATUS(status));
}
