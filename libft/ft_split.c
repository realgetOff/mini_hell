/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 21:20:21 by pmilner-          #+#    #+#             */
/*   Updated: 2025/04/27 16:35:37 by mforest-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	wordcount(char const *s, char c)
{
	int				words;
	unsigned int	i;

	words = 0;
	i = 0;
	if (s[0] != c && s[0])
		words++;
	while (s[i] && s[i + 1])
	{
		if (s[i] == c && s[i + 1] != c)
			words++;
		i++;
	}
	return (words);
}

static char	**freeall(char **c, int n)
{
	if (!c)
		return (NULL);
	while (n >= 0)
	{
		free(c[n]);
		n--;
	}
	free(c);
	return (NULL);
}

int	lettercount(const char *s, char c)
{
	unsigned int	i;
	unsigned int	letters;

	i = 0;
	letters = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (letters);
		else
			letters++;
		i++;
	}
	return (letters);
}

static char	**create_tab(char const *s, char c, char **ret)
{
	int	i;
	int	j;

	ret = (char **)malloc(sizeof(char *) * (wordcount(s, c) + 1));
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (lettercount(&s[i], c) && s[i])
		{
			ret[j] = (char *)malloc(sizeof(char) * (1 + lettercount(&s[i], c)));
			if (!ret[j])
				return (freeall(ret, j));
			j++;
			i += lettercount(&s[i], c);
		}
		else
			i++;
	}
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**ret;
	int		k;

	ret = NULL;
	ret = create_tab(s, c, ret);
	if (!ret)
		return (NULL);
	i = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			j = 0;
			while (s[i] != c && s[i])
				ret[k][j++] = s[i++];
			ret[k++][j] = '\0';
		}
	}
	ret[k] = NULL;
	return (ret);
}
