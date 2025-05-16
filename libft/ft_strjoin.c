/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 08:52:49 by pmilner-          #+#    #+#             */
/*   Updated: 2024/11/27 09:20:08 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	retsize;
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	retsize = ft_strlen(s1) + ft_strlen(s2) + 1;
	ret = (char *)malloc(sizeof(char) * retsize);
	if (!ret)
		return (NULL);
	while (s1[i] && s1)
	{
		ret[i] = s1[i];
		i++;
	}
	while (s2[j] && s2)
	{
		ret[i + j] = s2[j];
		j++;
	}
	ret[i + j] = '\0';
	return (ret);
}
