/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbasel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:55:43 by pmilner-          #+#    #+#             */
/*   Updated: 2024/11/26 10:45:00 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putbasel(size_t nbr, char *base, int bytes)
{
	size_t	temp;

	temp = ft_strlen(base);
	if (nbr >= temp)
	{
		bytes += ft_putbasel(nbr / temp, base, bytes);
		ft_putbasel(nbr % temp, base, bytes);
	}
	else
	{
		ft_putcharl(base[nbr]);
	}
	return (bytes + 1);
}
