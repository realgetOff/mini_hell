/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:08:18 by pmilner-          #+#    #+#             */
/*   Updated: 2024/10/17 03:21:41 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned long	i;

	if (!little[0])
		return ((char *)big);
	i = 0;
	while (big[i] && i < len)
	{
		if (!ft_strncmp(&big[i], little, ft_strlen(little)))
		{
			if (!(i + ft_strlen(little) > len))
				return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}
