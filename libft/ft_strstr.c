/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mforest- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 03:55:53 by mforest-          #+#    #+#             */
/*   Updated: 2025/03/05 04:03:28 by mforest-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	const char	*h = haystack;
	const char	*n = needle;

	if (!*needle)
		return ((char *)haystack);
	while (*haystack)
	{
		while (*n && *h == *n)
		{
			h++;
			n++;
		}
		if (!*n)
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}

char	*ft_double_strstr(const char *haystack, const char *needle)
{
	while (*haystack)
	{
		if (*haystack == needle[0] && *(haystack + 1) == needle[1])
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
