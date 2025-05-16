/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:08:46 by pmilner-          #+#    #+#             */
/*   Updated: 2025/04/26 22:24:58 by mforest-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

int	get_pipes(t_arguements *array)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (array[i].arg)
	{
		if (array[i].type == TOKEN_OPERATOR)
			count++;
		i++;
	}
	return (count);
}

char	**get_path_dirs(char **envp)
{
	int		i;
	char	*path;
	char	**dirs_split;

	i = 0;
	path = NULL;
	dirs_split = NULL;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5) && envp[i])
		{
			path = ft_strdup(envp[i] + 5);
			break ;
		}
		i++;
	}
	if (path)
		dirs_split = ft_split(path, ':');
	free(path);
	return (dirs_split);
}

int	**init_pipes(void)
{
	int	**pipefds;
	int	i;

	i = 0;
	pipefds = (int **)malloc(2 * sizeof(int *));
	if (!pipefds)
		return (NULL);
	while (i < 2)
	{
		pipefds[i] = (int *)malloc(2 * sizeof(int));
		if (!pipefds[i])
			return (NULL);
		pipe(pipefds[i]);
		i++;
	}
	return (pipefds);
}
