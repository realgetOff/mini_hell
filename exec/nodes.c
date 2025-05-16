/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 10:20:43 by pmilner-          #+#    #+#             */
/*   Updated: 2025/04/28 18:30:04 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

t_node	*create_node(char **cmd, int type)
{
	t_node	*node;

	node = (t_node *)ft_calloc(1, sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->cmd = cmd;
	return (node);
}

t_node	*create_nodes(t_arguements *array, t_exec *exec)
{
	char		***cmd;
	t_node		*first;
	t_iofiles	*io_array;
	int			pipe_count;

	pipe_count = get_pipes(array);
	cmd = get_cmd_args(array, pipe_count);
	io_array = get_all_fds(array, exec);
	if (pipe_count)
	{
		first = create_node(NULL, 0);
		set_cmds(first, cmd, pipe_count, io_array);
	}
	else
	{
		first = create_node(cmd[0], 1);
		first->io_fds = io_array[0];
	}
	free(cmd);
	free(io_array);
	return (first);
}
