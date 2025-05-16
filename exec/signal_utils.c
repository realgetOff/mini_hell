/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 02:08:21 by mforest-          #+#    #+#             */
/*   Updated: 2025/04/26 22:59:34 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

char	*get_signal_name(int signal)
{
	static char	*signal_names[] = {"SIGHUP", "SIGINT", "SIGQUIT", "SIGILL",
		"SIGTRAP", "SIGABRT", "SIGBUS", "SIGFPE", "SIGKILL", "SIGSEGV",
		"SIGPIPE", "SIGALRM", "SIGTERM", "SIGUSR1", "SIGUSR2", "SIGCHLD",
		"SIGCONT", "SIGSTOP", "SIGTSTP", "SIGTTIN", "SIGTTOU"};

	if (signal >= 1 && signal <= 22)
		return (signal_names[signal - 1]);
	return ("Unknown Signal");
}

void	print_signal(int signal)
{
	if (signal == SIGSEGV)
		ft_printf_err("Segmentation fault (core dumped)\n", stderr);
	else if (signal == SIGQUIT)
		ft_printf_err("Quit (core dumped)\n", stderr);
	else if (signal == SIGILL)
		ft_printf_err("Illegal instruction (core dumped)\n", stderr);
	else if (signal == SIGABRT)
		ft_printf_err("Aborted (core dumped)\n", stderr);
	else if (signal == SIGFPE)
		ft_printf_err("Floating point exception (core dumped)\n", stderr);
	else if (signal == SIGBUS)
		ft_printf_err("Bus error (core dumped)\n", stderr);
	else if (signal == SIGINT)
		write(1, "\n", 1);
}
