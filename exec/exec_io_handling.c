/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_io_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 21:19:38 by mforest-          #+#    #+#             */
/*   Updated: 2025/04/28 20:41:48 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

int	open_io_fd(char *arg, char *filename, t_exec *exec)
{
	int	fd;

	fd = -2;
	if (!ft_strcmp(arg, "<"))
		fd = open(filename, O_RDONLY);
	else if (!ft_strcmp(arg, "<<"))
		fd = handle_heredoc_fd(filename, exec);
	else if (!ft_strcmp(arg, ">"))
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else if (!ft_strcmp(arg, ">>"))
		fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	return (fd);
}

int	replace_io_fd(int old, char *arg, char *filename, t_exec *exec)
{
	int		new;
	char	*stripped;

	if (!ft_strncmp(arg, "<<", 2))
		stripped = ft_strdup(filename);
	else
		stripped = strip_quotes(filename);
	if (old > 2)
		close(old);
	new = open_io_fd(arg, stripped, exec);
	if (new == -1)
	{
		ft_printf_err("%s: ", filename);
		perror("");
	}
	if (new == -2)
		return (old);
	free(stripped);
	return (new);
}

void	get_io_files(t_arguements *array, t_iofiles *iostruct, t_exec *exec)
{
	int	i;

	i = 0;
	while (array[i].arg && array[i].type != TOKEN_OPERATOR)
	{
		if (array[i].type == TOKEN_REDIRECTION && array[i + 1].arg)
		{
			if (array[i].arg[0] == '<')
				iostruct->in = replace_io_fd(iostruct->in, array[i].arg, array[i
						+ 1].arg, exec);
			else
				iostruct->out = replace_io_fd(iostruct->out, array[i].arg,
						array[i + 1].arg, exec);
		}
		if (iostruct->in == -1 || iostruct->out == -1)
			break ;
		i++;
	}
}

t_iofiles	*get_all_fds(t_arguements *array, t_exec *exec)
{
	t_iofiles	*io_array;
	int			size;
	int			i;
	int			j;

	size = get_pipes(array) + 2;
	io_array = (t_iofiles *)ft_calloc(size, sizeof(t_iofiles));
	if (!io_array)
		return (NULL);
	j = 0;
	i = 0;
	while (array[i].arg)
	{
		get_io_files(&array[i], &io_array[j], exec);
		j++;
		while (array[i].arg && array[i].type != TOKEN_OPERATOR)
			i++;
		if (array[i].arg)
			i++;
	}
	return (io_array);
}

int	handle_heredoc_fd(char *filename, t_exec *exec)
{
	int		fd;
	char	*heredoc_content;

	heredoc_content = heredoc(filename, exec);
	if (!heredoc_content)
	{
		fd = -1;
		ft_printf_err("heredoc interrupted\n");
		return (fd);
	}
	temp_file_create(&fd, &exec->tmp_file);
	if (fd != -1)
	{
		write(fd, heredoc_content, ft_strlen(heredoc_content));
		close(fd);
		fd = open(exec->tmp_file, O_RDONLY);
	}
	free(heredoc_content);
	return (fd);
}
