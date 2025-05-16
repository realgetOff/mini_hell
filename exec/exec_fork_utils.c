/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:22:01 by pmilner-          #+#    #+#             */
/*   Updated: 2025/04/28 20:11:14 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

char	*get_path(char **dirs_split, char *command)
{
	char	*valid_path;
	char	*test_access;
	char	*temp;
	int		i;

	valid_path = NULL;
	i = 0;
	while (dirs_split[i] && !valid_path)
	{
		temp = ft_strjoin(dirs_split[i], "/");
		test_access = ft_strjoin(temp, command);
		if (!access(test_access, X_OK))
		{
			valid_path = test_access;
			break ;
		}
		if (!dirs_split[i + 1] && !valid_path)
			valid_path = ft_strjoin(temp, command);
		free(test_access);
		free(temp);
		test_access = NULL;
		i++;
	}
	return (valid_path);
}

char	*command_verif(t_iofiles *io_fds, t_exec *exec, char *command)
{
	char	*command_path;

	command_path = NULL;
	if (io_fds->in == -1 || io_fds->out == -1)
		exit_with_error(exec, EXIT_FAILURE, command);
	if (!command || !command[0])
		exit_with_error(exec, ENOENT, command);
	if (exec->path_dirs && !ft_strchr(command, '/'))
		command_path = get_path(exec->path_dirs, command);
	else if (command_path && !access(command, X_OK) && !ft_strchr(command, '/'))
		exit_with_error(exec, ENOENT, command);
	if (!command_path && !access(command, X_OK))
		command_path = command;
	else if (!command_path && access(command, X_OK) == -1)
		exit_with_error(exec, errno, command);
	return (command_path);
}

void	free_node_fds(t_node *node, int **pipe, t_iofiles *cmdio)
{
	if (!node)
		return ;
	free_node_fds(node->left, pipe, cmdio);
	free_node_fds(node->right, pipe, cmdio);
	if (cmdio->in != node->io_fds.in && cmdio->out != node->io_fds.out)
	{
		if (node->io_fds.in != pipe[0][0] && node->io_fds.out != pipe[0][0])
			close(node->io_fds.in);
		if (node->io_fds.in != pipe[1][1] && node->io_fds.out != pipe[1][1])
			close(node->io_fds.out);
	}
}

void	close_useless_fds(t_iofiles *cmdio, int **pipefds, t_exec *exec)
{
	int	i;

	i = 0;
	free_node_fds(exec->first, pipefds, cmdio);
	if (exec->saved_out != cmdio->out)
		close(exec->saved_out);
	while (i < 2)
	{
		if (cmdio->in != pipefds[i][0] && cmdio->out != pipefds[i][0])
			close_after_use(&pipefds[i][0]);
		if (cmdio->in != pipefds[i][1] && cmdio->out != pipefds[i][1])
			close_after_use(&pipefds[i][1]);
		i++;
	}
}
