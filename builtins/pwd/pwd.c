/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 02:46:32 by pmilner-          #+#    #+#             */
/*   Updated: 2025/04/03 03:23:00 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

void	pwd(t_exec *exec, t_node *node)
{
	char	*pwd;

	(void) node;
	pwd = getcwd(NULL, PATH_MAX);
	if (!pwd)
	{
		ft_printf_err("pwd: error retrieving current directory\n");
		exec->data->exit_code = 1;
		return ;
	}
	printf("%s\n", pwd);
	free(pwd);
	exec->data->exit_code = 0;
}
