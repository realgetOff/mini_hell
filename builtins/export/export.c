/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 09:24:37 by pmilner-          #+#    #+#             */
/*   Updated: 2025/04/26 22:52:28 by mforest-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

int	export(t_read *entry, char **split)
{
	if (!split[0][0] || !check_name_validity(split[0]))
	{
		ft_printf_err("export: '%s': not a valid identifier\n", split[0]);
		return (1);
	}
	if (!split[1])
	{
		add_to_exports(entry, split[0]);
		return (0);
	}
	append_equals(&split[0]);
	if (!ft_strncmp(split[1], "+=", 2))
	{
		append_env(entry, split[0], split[2]);
		return (0);
	}
	set_env(entry, split[0], split[2]);
	return (0);
}

void	ft_export(t_exec *exec, t_node *node)
{
	char	**export_arr;
	int		ac;
	int		i;

	i = 1;
	ac = 0;
	while (node->cmd[ac])
		ac++;
	if (ac == 1)
	{
		solo_export_cmd(exec->entry);
		exec->data->exit_code = 0;
		return ;
	}
	while (node->cmd[i])
	{
		export_arr = export_split(node->cmd[i]);
		exec->data->exit_code = export(exec->entry, export_arr);
		free_str_array(export_arr);
		i++;
	}
}
