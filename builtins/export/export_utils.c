/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 22:05:22 by mforest-          #+#    #+#             */
/*   Updated: 2025/04/26 22:52:21 by mforest-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

int	check_name_validity(char *var_name)
{
	int	i;

	i = 0;
	if (ft_isdigit(var_name[0]))
		return (0);
	while (var_name[i])
	{
		if (!ft_isalnum(var_name[i]) && var_name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	append_equals(char **str)
{
	char	*tmp;
	int		len;

	len = ft_strlen(*str) + 2;
	tmp = (char *)ft_calloc(len, sizeof(char));
	if (!tmp)
		return ;
	ft_strcpy(tmp, *str);
	tmp = ft_strcat(tmp, "=");
	free(*str);
	*str = tmp;
}
