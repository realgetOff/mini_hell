/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 04:32:09 by pmilner-          #+#    #+#             */
/*   Updated: 2025/03/05 20:17:24 by mforest-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned long	dstinit;
	unsigned long	i;	
	unsigned long	srcinit;

	if (size == 0)
		return (ft_strlen(src));
	i = 0;
	srcinit = ft_strlen(src);
	dstinit = ft_strlen(dst);
	if (dstinit >= size)
		return (size + ft_strlen(src));
	while (i < (size - dstinit - 1) && src[i])
	{
		dst[dstinit + i] = src[i];
		i++;
	}
	dst[dstinit + i] = '\0';
	return (dstinit + srcinit);
}
