/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_four.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mforest- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 22:53:39 by mforest-          #+#    #+#             */
/*   Updated: 2025/04/26 22:55:44 by mforest-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

static int	check_export_skip(t_read *entry, int j)
{
	int	k;

	k = 0;
	while (entry->envp && entry->envp[k])
	{
		if (!ft_strncmp(entry->envp[k], entry->exports[j],
				ft_strlen(entry->exports[j]))
			&& entry->envp[k][ft_strlen(entry->exports[j])] == '=')
			return (1);
		k++;
	}
	return (0);
}

static void	print_env_vars(t_read *entry)
{
	int	j;

	j = 0;
	while (entry->envp[j] != 0)
	{
		export_single_var(ft_strdup(entry->envp[j]));
		j++;
	}
}

static void	print_export_vars(t_read *entry)
{
	int	j;

	j = 0;
	while (entry->exports && entry->exports[j] != 0)
	{
		if (!check_export_skip(entry, j))
			export_single_var(ft_strdup(entry->exports[j]));
		j++;
	}
}

void	solo_export_cmd(t_read *entry)
{
	print_env_vars(entry);
	print_export_vars(entry);
}
