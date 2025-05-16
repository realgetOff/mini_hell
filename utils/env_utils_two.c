/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mforest- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 23:01:39 by mforest-          #+#    #+#             */
/*   Updated: 2025/04/26 23:14:35 by mforest-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

static char	*create_new_contents(char *var_name, char *contents)
{
	int		var_len;
	char	*new_contents;

	var_len = ft_strlen(var_name);
	if (contents)
		var_len += ft_strlen(contents);
	new_contents = (char *)malloc(sizeof(char) * (var_len + 1));
	if (!new_contents)
		return (NULL);
	ft_strcpy(new_contents, var_name);
	if (contents)
		new_contents = ft_strcat(new_contents, contents);
	return (new_contents);
}

char	*create_env_var(char *var_name, char *contents)
{
	int		var_len;
	char	*new_var;

	var_len = ft_strlen(var_name);
	if (contents)
		var_len += ft_strlen(contents);
	new_var = (char *)ft_calloc(sizeof(char), (var_len + 1));
	if (!new_var)
		return (NULL);
	ft_strcpy(new_var, var_name);
	if (contents)
		new_var = ft_strcat(new_var, contents);
	return (new_var);
}

int	find_var_index(char **envp, char *var_name)
{
	int	i;
	int	var_len;

	i = 0;
	var_len = ft_strlen(var_name);
	while (envp[i] && ft_strncmp(envp[i], var_name, var_len))
		i++;
	return (i);
}

void	set_env_var(t_read *entry, char *var_name, char *contents, int i)
{
	char	*new_contents;

	new_contents = create_new_contents(var_name, contents);
	if (!new_contents)
		return ;
	free(entry->envp[i]);
	entry->envp[i] = new_contents;
}

void	append_env_var(t_read *entry, char *to_add, int i)
{
	int		var_len;
	char	*new_var;

	if (!to_add)
		return ;
	var_len = ft_strlen(to_add);
	var_len += ft_strlen(entry->envp[i]);
	new_var = (char *)malloc(sizeof(char) * (var_len + 1));
	if (!new_var)
		return ;
	ft_strcpy(new_var, entry->envp[i]);
	new_var = ft_strcat(new_var, to_add);
	free(entry->envp[i]);
	entry->envp[i] = new_var;
}
