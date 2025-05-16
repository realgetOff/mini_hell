/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:09:29 by pmilner-          #+#    #+#             */
/*   Updated: 2024/10/17 23:31:00 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_findsize(int n)
{
	int	ret;

	ret = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		ret++;
	while (n)
	{
		n /= 10;
		ret += 1;
	}
	return (ret);
}

static char	*ft_conversion(int n, int negative, size_t size)
{
	char	*ret;

	ret = (char *)malloc(sizeof(char) * (size + 1));
	if (!ret)
		return (NULL);
	ret[size] = '\0';
	size--;
	while (size + !(negative))
	{
		ret[size] = ((n % 10) * !negative) - ((n % 10) * negative) + '0';
		n = n / 10;
		size--;
	}
	if (negative)
		ret[0] = '-';
	return (ret);
}

char	*ft_itoa(int n)
{
	size_t	size;
	int		negative;

	negative = 0;
	size = ft_findsize(n);
	if (n < 0)
		negative = 1;
	return (ft_conversion(n, negative, size));
}
