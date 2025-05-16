/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_three.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 22:33:05 by mforest-          #+#    #+#             */
/*   Updated: 2025/04/28 03:46:44 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

char	**export_split(char *in)
{
	int		i;
	int		j;
	int		k;
	char	**out;

	initialise_ijk(&i, &j, &k);
	out = alloc_split(in);
	while (in[i] && (ft_strncmp(&in[i], "+=", 2) && in[i] != '='))
		out[k][j++] = in[i++];
	if (!in[i])
		return (out);
	k++;
	j = 0;
	if (in[i] && (in[i] == '+'))
		out[k][j++] = in[i++];
	if (in[i] && (in[i] == '='))
		out[k][j++] = in[i++];
	if (!in[i])
		return (out);
	k++;
	j = 0;
	while (in[i])
		out[k][j++] = in[i++];
	return (out);
}
