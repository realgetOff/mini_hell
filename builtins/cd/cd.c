/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 03:18:17 by pmilner-          #+#    #+#             */
/*   Updated: 2025/04/28 00:33:02 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

static int	check_args(t_data *data, t_node *node)
{
	int	i;

	i = 0;
	while (node->cmd[i])
	{
		if (i > 1)
		{
			ft_printf_err("mini_hell: cd: too many arguments\n");
			data->exit_code = 1;
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

void	change_dir(t_exec *exec, t_node *node)
{
	char	*path;
	char	*home;

	home = NULL;
	if (!node->cmd[1])
	{
		home = get_var(exec->entry, "HOME=");
		if (!home)
		{
			exec->data->exit_code = 1;
			return ;
		}
		path = home;
	}
	else
		path = node->cmd[1];
	if (chdir(path) == -1)
	{
		ft_printf_err("mini_hell: cd: %s: No such file or directory\n", path);
		exec->data->exit_code = 1;
		free(home);
		return ;
	}
	free(home);
}

void	cd(t_exec *exec, t_node *node)
{
	char	*oldpwd;
	char	*pwd;

	if (check_args(exec->data, node) == EXIT_FAILURE)
		return ;
	oldpwd = NULL;
	oldpwd = getcwd(NULL, PATH_MAX);
	change_dir(exec, node);
	if (exec->data->exit_code)
	{
		free(oldpwd);
		return ;
	}
	pwd = getcwd(NULL, PATH_MAX);
	set_env(exec->entry, "PWD=", pwd);
	free(pwd);
	set_env(exec->entry, "OLDPWD=", oldpwd);
	free(oldpwd);
	exec->data->exit_code = 0;
}
