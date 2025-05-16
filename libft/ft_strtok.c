/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mforest- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 03:51:39 by mforest-          #+#    #+#             */
/*   Updated: 2025/03/05 03:52:38 by mforest-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *str, char *delim)
{
	static char	*last = 0;
	char		*start;

	if (!str)
		str = last;
	if (!str)
		return (0);
	while (*str && ft_strchr(delim, *str))
		str++;
	if (!*str)
	{
		last = 0;
		return (0);
	}
	start = str;
	while (*str && !ft_strchr(delim, *str))
		str++;
	if (*str)
	{
		*str = '\0';
		last = str + 1;
	}
	else
		last = 0;
	return (start);
}
