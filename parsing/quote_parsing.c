/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 01:44:25 by pmilner-          #+#    #+#             */
/*   Updated: 2025/04/26 23:02:22 by mforest-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

char	*strip_quotes(char *line)
{
	char	*ret;
	int		i;
	int		j;
	int		size;

	ret = (char *)malloc(sizeof(char *) * (getsize_stripped(line) + 1));
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	size = (int)ft_strlen(line);
	while (i < size && line[i])
		process_quotes(ret, line, &i, &j);
	ret[j] = '\0';
	return (ret);
}

void	strip_all_quotes(char **entry)
{
	int		i;
	char	*tmp;

	i = 0;
	while (entry[i])
	{
		tmp = strip_quotes(entry[i]);
		free(entry[i]);
		entry[i] = tmp;
		i++;
	}
}
