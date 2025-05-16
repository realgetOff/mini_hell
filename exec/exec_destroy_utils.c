/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_destroy_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:14:14 by pmilner-          #+#    #+#             */
/*   Updated: 2025/04/26 22:24:44 by mforest-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

void	pipeline_cleanup(int **pipefds)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		close_after_use(&pipefds[i][0]);
		close_after_use(&pipefds[i][1]);
		free(pipefds[i]);
		i++;
	}
	free(pipefds);
}

void	free_nodes(t_node *node)
{
	if (!node)
		return ;
	free_nodes(node->left);
	free_nodes(node->right);
	if (node->cmd)
		free_str_array(node->cmd);
	if (node->io_fds.in > 2)
		close(node->io_fds.in);
	if (node->io_fds.out > 2)
		close(node->io_fds.out);
	free(node);
}
