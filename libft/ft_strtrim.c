/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:02:27 by pmilner-          #+#    #+#             */
/*   Updated: 2024/10/17 23:39:15 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	chrcmp(char const c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	int		start;
	int		end;
	int		i;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	i = 0;
	end = ft_strlen(s1) - 1;
	while (chrcmp(s1[start], set) && s1[start])
		start++;
	if (start > end)
		return (ft_strdup(&s1[end + 1]));
	while (chrcmp(s1[end], set) && end >= 0)
		end--;
	ret = (char *)malloc(sizeof(char) * (2 + end - start));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, &s1[start], 2 + end - start);
	return (ret);
}
