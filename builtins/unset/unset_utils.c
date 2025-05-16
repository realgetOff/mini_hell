/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 21:09:38 by mforest-          #+#    #+#             */
/*   Updated: 2025/04/26 16:58:42 by mforest-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

void	unset_check_null_params(t_exec *exec, t_node *node)
{
	if (!exec || !exec->envp || !node || !node->cmd)
		return ;
}

void	unset_free_envp_dup(char **envp_dup, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(envp_dup[i]);
		i++;
	}
	free(envp_dup);
}

void	unset_free_old_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		envp[i] = NULL;
		i++;
	}
	free(envp);
}

char	**unset_alloc_new_envp(t_exec *exec)
{
	int		i;
	char	**envp_dup;

	i = 0;
	while (exec->envp[i])
		i++;
	envp_dup = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!envp_dup)
		return (NULL);
	return (envp_dup);
}

void	unset_process_variable(t_exec *exec, char *var_name, char **envp_dup,
		int var_size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (exec->envp[i])
	{
		if (ft_strncmp(var_name, exec->envp[i], var_size) == 0
			&& (exec->envp[i][var_size] == '='
			|| exec->envp[i][var_size] == '\0'))
			i++;
		else
		{
			envp_dup[j] = ft_strdup(exec->envp[i]);
			if (!envp_dup[j])
			{
				unset_free_envp_dup(envp_dup, j);
				return ;
			}
			j++;
			i++;
		}
	}
}
