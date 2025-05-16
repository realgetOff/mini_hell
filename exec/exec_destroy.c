/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:14:14 by pmilner-          #+#    #+#             */
/*   Updated: 2025/04/27 21:58:12 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

void	destroy_exec(t_exec *exec_st)
{
	int	i;

	i = 0;
	while (exec_st->tokens[i].arg)
		free(exec_st->tokens[i++].arg);
	free(exec_st->tokens);
	if (exec_st->tmp_file)
	{
		unlink(exec_st->tmp_file);
		free(exec_st->tmp_file);
	}
	if (exec_st->path_dirs)
		free_str_array(exec_st->path_dirs);
	if (exec_st->saved_out != -1 && exec_st->saved_out != 1)
		close (exec_st->saved_out);
	pipeline_cleanup(exec_st->pipefds);
	free_nodes(exec_st->first);
}
