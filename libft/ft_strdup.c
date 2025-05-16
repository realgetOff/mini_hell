/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 08:52:24 by pmilner-          #+#    #+#             */
/*   Updated: 2024/11/27 08:52:41 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	size;
	char	*buffer;
	int		i;

	i = 0;
	size = ft_strlen(s);
	buffer = (char *)malloc((sizeof(char) * size) + 1);
	if (!buffer)
		return (0);
	while (s[i])
	{
		buffer[i] = s[i];
		i++;
	}
	buffer[size] = '\0';
	return (buffer);
}
