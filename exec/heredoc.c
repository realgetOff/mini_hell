/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 01:43:06 by pmilner-          #+#    #+#             */
/*   Updated: 2025/04/28 20:44:08 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

static int	is_delimiter(char *line, char *delimiter)
{
	int		i;
	int		delim_len;
	char	*stripped;
	int		ret;

	i = 0;
	stripped = strip_quotes(delimiter);
	delim_len = (int)ft_strlen(stripped);
	while (line[i] && line[i] != '\n')
		i++;
	if (i != delim_len)
	{
		free(stripped);
		return (0);
	}
	ret = ft_strncmp(line, stripped, i) == 0;
	free(stripped);
	return (ret);
}

static char	*expand_heredoc(char *read, t_exec *exec, char *delimiter)
{
	char	*expand;

	expand = NULL;
	if (!ft_strchr(delimiter, '"') && !ft_strchr(delimiter, '\''))
		expand = expansion(exec->entry, read, exec->data);
	else
		expand = read;
	return (expand);
}

static char	*process_heredoc_line(char *stdin_read, char *temp)
{
	char	*in_temp;

	in_temp = temp;
	temp = ft_strjoin(temp, "\n");
	free(in_temp);
	in_temp = stdin_read;
	stdin_read = ft_strjoin(stdin_read, temp);
	free(in_temp);
	free(temp);
	return (stdin_read);
}

char	*heredoc(char *delimiter, t_exec *exec)
{
	char	*stdin_read;
	char	*temp;
	char	*stripped;

	stdin_read = ft_strdup("");
	stripped = strip_quotes(delimiter);
	temp = NULL;
	while (1)
	{
		temp = readline("> ");
		if (!temp || g_signal_pid != 0)
		{
			free(stripped);
			free(stdin_read);
			return (NULL);
		}
		if (is_delimiter(temp, stripped))
			break ;
		stdin_read = process_heredoc_line(stdin_read, temp);
		temp = NULL;
	}
	stdin_read = expand_heredoc(stdin_read, exec, delimiter);
	free(temp);
	free(stripped);
	return (stdin_read);
}
