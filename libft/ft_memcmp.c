/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 00:21:48 by pmilner-          #+#    #+#             */
/*   Updated: 2024/10/17 03:13:43 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t len)
{
	unsigned long	i;
	unsigned char	*s1itp;
	unsigned char	*s2itp;

	s1itp = (unsigned char *)s1;
	s2itp = (unsigned char *)s2;
	i = 0;
	if (!len)
		return (0);
	while (s1itp[i] == s2itp[i] && i < len - 1)
	{
		i++;
	}
	return (s1itp[i] - s2itp[i]);
}
