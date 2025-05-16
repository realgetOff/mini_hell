/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 01:18:52 by pmilner-          #+#    #+#             */
/*   Updated: 2025/04/26 23:14:30 by mforest-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

int	envlen(t_read *entry)
{
	int	i;

	if (!entry->envp)
		return (0);
	i = 0;
	while (entry->envp[i])
		i++;
	return (i);
}

void	create_env(t_read *entry, char *var_name, char *contents)
{
	int		i;
	char	**new_envp;
	char	*new_var;

	new_envp = (char **)ft_calloc(sizeof(char *), (envlen(entry) + 2));
	if (!new_envp)
		return ;
	i = 0;
	while (entry->envp[i])
	{
		new_envp[i] = entry->envp[i];
		i++;
	}
	new_var = create_env_var(var_name, contents);
	if (!new_var)
		return ;
	new_envp[i] = new_var;
	free(entry->envp);
	entry->envp = new_envp;
}

void	set_env(t_read *entry, char *var_name, char *contents)
{
	char	*temp;

	temp = get_var(entry, var_name);
	if (!entry->envp || !temp[0])
	{
		free(temp);
		create_env(entry, var_name, contents);
		return ;
	}
	free(temp);
	set_env_var(entry, var_name, contents, find_var_index(entry->envp,
			var_name));
}

void	append_env(t_read *entry, char *var_name, char *to_add)
{
	int	i;

	i = find_var_index(entry->envp, var_name);
	if (!entry->envp[i])
	{
		create_env(entry, var_name, to_add);
		return ;
	}
	append_env_var(entry, to_add, i);
}

char	*get_var(t_read *entry, char *var_name)
{
	int		i;
	char	*ret;
	int		var_len;

	i = 0;
	ret = ft_strdup("");
	if (!entry->envp)
		return (ret);
	var_len = ft_strlen(var_name);
	while (entry->envp[i] && ft_strncmp(entry->envp[i], var_name, var_len))
		i++;
	if (!entry->envp[i])
		return (ret);
	free(ret);
	ret = ft_strdup(&entry->envp[i][var_len]);
	return (ret);
}
