/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:14:37 by pmilner-          #+#    #+#             */
/*   Updated: 2024/10/17 03:14:47 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*destint;
	const unsigned char	*srcint;

	destint = (unsigned char *)dest;
	srcint = (const unsigned char *)src;
	if (destint == srcint || n == 0)
		return (destint);
	if (destint < srcint)
	{
		while (n--)
			*destint++ = *srcint++;
	}
	else
	{
		while (n--)
			*(destint + n) = *(srcint + n);
	}
	return (dest);
}
