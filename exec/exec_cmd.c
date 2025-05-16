/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:25:23 by pmilner-          #+#    #+#             */
/*   Updated: 2025/04/27 02:18:17 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

char	***get_cmd_args(t_arguements *array, int size)
{
	char	***ret;
	int		i;
	int		j;

	ret = (char ***)ft_calloc(size + 2, sizeof(char **));
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	while (array[i].arg)
	{
		ret[j++] = create_cmd_array(&array[i]);
		while (array[i].arg && array[i].type != TOKEN_OPERATOR)
			i++;
		if (array[i].arg)
			i++;
	}
	return (ret);
}

t_node	*set_cmds(t_node *current, char ***cmds, int layer, t_iofiles *io_fds)
{
	if (layer == 1)
	{
		current->left = create_node(cmds[layer - 1], 1);
		current->left->io_fds = io_fds[layer - 1];
		current->right = create_node(cmds[layer], 1);
		current->right->io_fds = io_fds[layer];
	}
	else
	{
		current->left = create_node(NULL, 0);
		set_cmds(current->left, cmds, layer - 1, io_fds);
		current->right = create_node(cmds[layer], 1);
		current->right->io_fds = io_fds[layer];
	}
	return (current);
}
