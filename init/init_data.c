/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 01:09:42 by mforest-          #+#    #+#             */
/*   Updated: 2025/04/28 03:55:06 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

static char	**dup_envp(char **envp)
{
	int		i;
	char	**envp_dup;

	i = 0;
	while (envp[i])
		i++;
	envp_dup = (char **)malloc(sizeof(char *) * (i + 1));
	if (!envp_dup)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		envp_dup[i] = ft_strdup(envp[i]);
		i++;
	}
	envp_dup[i] = NULL;
	return (envp_dup);
}

void	init_data(t_data *data, char **envp)
{
	char	*pwd;

	data->s_read = malloc(sizeof(t_read));
	if (!data->s_read)
		return ;
	data->s_history = malloc(sizeof(t_history));
	if (!data->s_history)
		return ;
	ft_memset(data->s_history->history_buffer, 0,
		sizeof(data->s_history->history_buffer));
	data->exit_code = 0;
	data->s_read->executed = 0;
	data->s_history->history_index = 0;
	data->s_history->history_count = 0;
	data->s_read->envp = dup_envp(envp);
	data->s_read->line = NULL;
	data->s_read->exports = NULL;
	pwd = getcwd(NULL, PATH_MAX);
	set_env(data->s_read, "PWD=", pwd);
	free(pwd);
	using_history();
	setup_signals(data);
	print_art();
}
