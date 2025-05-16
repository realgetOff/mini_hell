/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mforest- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 22:33:05 by mforest-          #+#    #+#             */
/*   Updated: 2025/04/26 22:55:38 by mforest-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

void	export_single_var(char *env_var)
{
	char	*eq_ptr;

	eq_ptr = ft_strchr(env_var, '=');
	if (eq_ptr)
	{
		*eq_ptr = '\0';
		printf("declare -x %s=\"%s\"\n", env_var, eq_ptr + 1);
	}
	else
		printf("declare -x %s\n", env_var);
	free(env_var);
}

void	add_to_exports(t_read *entry, char *name)
{
	int		i;
	char	**new_exports;
	char	*new_var;

	i = 0;
	while (entry->exports && entry->exports[i])
		i++;
	new_exports = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_exports)
		return ;
	i = 0;
	while (entry->exports && entry->exports[i])
	{
		new_exports[i] = entry->exports[i];
		i++;
	}
	new_var = ft_strdup(name);
	new_exports[i] = new_var;
	new_exports[i + 1] = NULL;
	if (entry->exports)
		free(entry->exports);
	entry->exports = new_exports;
}
