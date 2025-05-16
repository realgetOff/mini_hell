/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:08:46 by pmilner-          #+#    #+#             */
/*   Updated: 2025/04/27 02:18:30 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

t_exec	init_exec(t_read *entry, t_data *data)
{
	t_exec	exec_st;

	exec_st.tokens = entry->tokens;
	exec_st.entry = entry;
	exec_st.data = data;
	exec_st.pipefds = init_pipes();
	exec_st.envp = entry->envp;
	exec_st.path_dirs = get_path_dirs(entry->envp);
	exec_st.cmd_count = get_pipes(exec_st.tokens) + 1;
	exec_st.tmp_file = NULL;
	exec_st.first = create_nodes(exec_st.tokens, &exec_st);
	exec_st.saved_out = dup(STDOUT_FILENO);
	return (exec_st);
}
