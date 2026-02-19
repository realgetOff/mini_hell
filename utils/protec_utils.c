/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protec_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 00:56:04 by pmilner-          #+#    #+#             */
/*   Updated: 2025/04/29 00:59:26 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

void	free_arrayarray(void **arrayarray)
{
	int	i;

	i = 0;
	while (arrayarray[i])
		free(arrayarray[i++]);
	free(arrayarray);
}

void	free_threestar(void ***threestar)
{
	int i = 0;

	while (threestar[i])
		free_arrayarray(threestar[i++]);
	free (threestar);
}
