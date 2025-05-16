/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 03:53:35 by pmilner-          #+#    #+#             */
/*   Updated: 2025/03/31 21:57:13 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

void	env(t_exec *exec, t_node *node)
{
	int	i;

	if (node->cmd[1])
	{
		exec->data->exit_code = 1;
		return ;
	}
	i = 0;
	while (exec->entry->envp[i])
	{
		printf("%s\n", exec->entry->envp[i]);
		i++;
	}
	exec->data->exit_code = 0;
}
