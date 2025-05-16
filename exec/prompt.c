/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 02:23:30 by mforest-          #+#    #+#             */
/*   Updated: 2025/04/23 02:29:27 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

static void	format_prompt_with_home(char *prompt, char *home, char *current_dir)
{
	if (ft_strncmp(current_dir, home, ft_strlen(home)) == 0)
	{
		ft_strcat(prompt, "~");
		ft_strcat(prompt, current_dir + ft_strlen(home));
	}
	else
		ft_strcat(prompt, current_dir);
	free(current_dir);
}

void	prompt_get_dir(char *prompt, t_data *data)
{
	char	*home;
	char	*new_dir;

	if (!data || !data->s_read)
		return ;
	home = getenv("HOME");
	data->s_read->current_dir = getcwd(NULL, PATH_MAX);
	if (!data->s_read->current_dir)
		data->s_read->current_dir = ft_strdup("/");
	new_dir = getcwd(NULL, PATH_MAX);
	if (new_dir)
	{
		free(data->s_read->current_dir);
		data->s_read->current_dir = new_dir;
	}
	else
		free(new_dir);
	if (!home)
		ft_strcat(prompt, data->s_read->current_dir);
	else
		format_prompt_with_home(prompt, home, data->s_read->current_dir);
}

void	generate_prompt(char *prompt, t_data *data)
{
	char	*user;

	user = getenv("USER");
	if (!user)
		ft_strcpy(prompt, "unknown@mini_hell:");
	else
	{
		ft_strcpy(prompt, user);
		ft_strcat(prompt, "\001\e[1;97m\002@mini_hell\001\e[0m\002:");
	}
	prompt_get_dir(prompt, data);
	ft_strcat(prompt, "$ ");
}
