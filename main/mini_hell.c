/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_hell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 06:51:25 by mforest-          #+#    #+#             */
/*   Updated: 2025/04/28 03:55:10 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

pid_t	g_signal_pid;

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	char	*line;

	(void)ac;
	(void)av;
	init_data(&data, envp);
	while (true)
	{
		g_signal_pid = 0;
		generate_prompt(data.s_read->prompt, &data);
		line = readline(data.s_read->prompt);
		check_for_sigint(&data);
		if (!line)
			exit_errorcode(&data, data.exit_code);
		if (*line)
			add_to_history_buffer(line, &data);
		lexer(line, &data, data.s_read);
		if (!data.s_read->line)
		{
			free(line);
			continue ;
		}
		data.s_read->line = NULL;
	}
	return (0);
}
