/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_io_handling_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:19:59 by pmilner-          #+#    #+#             */
/*   Updated: 2025/04/27 02:18:51 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

void	handle_override(t_node *node, int **pipefds, int layer, int max)
{
	if (!node->io_fds.in && layer == 1)
		node->io_fds.in = 0;
	else if (!node->io_fds.in)
		node->io_fds.in = pipefds[(layer + 1) % 2][0];
	if (!node->io_fds.out && layer == max)
		node->io_fds.out = 1;
	else if (!node->io_fds.out)
		node->io_fds.out = pipefds[layer % 2][1];
}

void	temp_file_create(int *fd, char **filename)
{
	int	tempfd;
	int	urandomfd;

	if (*filename)
	{
		unlink(*filename);
		free(*filename);
	}
	*filename = (char *)ft_calloc(sizeof(char), 9);
	if (!filename)
		return ;
	urandomfd = open("/dev/urandom", O_RDONLY);
	tempfd = -1;
	while (tempfd == -1)
	{
		read(urandomfd, *filename, 8);
		tempfd = open(*filename, O_EXCL | O_CREAT | O_RDWR, S_IRWXU);
	}
	close(urandomfd);
	*fd = tempfd;
}
