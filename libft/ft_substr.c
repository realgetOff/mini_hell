/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 08:54:44 by pmilner-          #+#    #+#             */
/*   Updated: 2024/11/27 08:55:00 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	rest;
	size_t	j;
	char	*substr;	

	if (start >= ft_strlen(s))
		return (0);
	rest = ft_strlen(&s[start]);
	if (rest < len)
		substr = (char *)malloc(sizeof(char) * (rest + 1));
	else
		substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	j = 0;
	while (s[start] && j < len)
	{
		substr[j] = s[start];
		start++;
		j++;
	}
	substr[j] = '\0';
	return (substr);
}
