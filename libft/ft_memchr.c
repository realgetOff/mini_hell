/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 00:58:31 by pmilner-          #+#    #+#             */
/*   Updated: 2024/10/17 23:43:24 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s1, int c, size_t n)
{
	unsigned long	i;
	unsigned char	*s1itp;

	i = 0;
	s1itp = (unsigned char *)s1;
	while (i < n)
	{
		if (s1itp[i] == (unsigned char) c)
			return (&s1itp[i]);
		i++;
	}
	return (NULL);
}
