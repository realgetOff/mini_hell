/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 02:04:42 by pmilner-          #+#    #+#             */
/*   Updated: 2025/04/16 20:16:01 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

void	unset_update_exec_envp(t_exec *exec, char **envp_dup)
{
	exec->envp = envp_dup;
	exec->entry->envp = envp_dup;
}

void	unset(t_exec *exec, t_node *node)
{
	int		arg_index;
	char	**envp_dup;

	unset_check_null_params(exec, node);
	arg_index = 1;
	while (node->cmd[arg_index])
	{
		envp_dup = unset_alloc_new_envp(exec);
		if (!envp_dup)
			return ;
		unset_process_variable(exec, node->cmd[arg_index], envp_dup,
			ft_strlen(node->cmd[arg_index]));
		unset_free_old_envp(exec->envp);
		unset_update_exec_envp(exec, envp_dup);
		arg_index++;
	}
	exec->data->exit_code = 0;
}
