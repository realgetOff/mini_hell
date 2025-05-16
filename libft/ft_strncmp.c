/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:02:27 by pmilner-          #+#    #+#             */
/*   Updated: 2024/10/17 03:20:00 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned long	i;
	unsigned char	*s1itp;
	unsigned char	*s2itp;

	s1itp = (unsigned char *)s1;
	s2itp = (unsigned char *)s2;
	i = 0;
	if (!n)
		return (0);
	while (s1itp[i] == s2itp[i] && i < n - 1 && s1itp[i] && s2itp[i])
		i++;
	return (s1itp[i] - s2itp[i]);
}
