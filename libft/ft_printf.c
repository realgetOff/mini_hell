/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:33:43 by pmilner-          #+#    #+#             */
/*   Updated: 2024/11/26 10:44:31 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	putint(int nbr)
{
	long int	temp;
	size_t		bytes;

	bytes = 0;
	if (nbr < 0)
	{
		temp = (long int) nbr;
		bytes += ft_putcharl('-');
		bytes += ft_putbasel(-temp, "0123456789", 0);
	}
	else
		bytes = ft_putbasel(nbr, "0123456789", 0);
	return (bytes);
}

static int	putmem(size_t adr)
{
	size_t	bytes;

	bytes = 0;
	if (!adr)
		bytes = ft_putstrl("(nil)");
	else
	{
		bytes += ft_putstrl("0x");
		bytes += ft_putbasel(adr, "0123456789abcdef", 0);
	}
	return (bytes);
}

static int	parsevar(char c, va_list vars)
{
	size_t	ret;

	if (c == '%')
		ret = ft_putcharl('%');
	else if (c == 'c')
		ret = ft_putcharl(va_arg(vars, int));
	else if (c == 's')
		ret = ft_putstrl(va_arg(vars, const char *));
	else if (c == 'p')
		ret = putmem((size_t)va_arg(vars, void *));
	else if (c == 'd' || c == 'i')
		ret = putint(va_arg(vars, int));
	else if (c == 'u')
		ret = ft_putbasel(va_arg(vars, unsigned int), "0123456789", 0);
	else if (c == 'x')
		ret = ft_putbasel(va_arg(vars, unsigned int), "0123456789abcdef", 0);
	else if (c == 'X')
		ret = ft_putbasel(va_arg(vars, unsigned int), "0123456789ABCDEF", 0);
	else
	{
		ret = ft_putcharl('%');
		ret += ft_putcharl(c);
	}
	return (ret);
}

int	ft_printf(const char *s, ...)
{
	int		i;
	int		bytes;
	va_list	vars;

	bytes = 0;
	i = 0;
	if (!s)
		return (-1);
	va_start(vars, s);
	while (s[i])
	{
		if (s[i] == '%' && !s[i + 1])
			return (-1);
		else if (s[i] == '%')
			bytes += parsevar(s[++i], vars) - 2;
		else
			ft_putcharl(s[i]);
		i++;
	}
	va_end(vars);
	return (i + bytes);
}
