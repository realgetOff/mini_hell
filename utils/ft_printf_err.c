/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_err.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:53:09 by pmilner-          #+#    #+#             */
/*   Updated: 2025/03/16 02:25:02 by mforest-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

int	ft_putstrl_fd(const char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
	{
		ft_putstrl_fd("(null)", fd);
		return (6);
	}
	while (s[i])
		write (fd, &s[i++], 1);
	return (i);
}

static int	ft_putcharl_fd(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

static int	parsevar(char c, va_list vars)
{
	size_t	ret;

	if (c == 's')
		ret = ft_putstrl_fd(va_arg(vars, const char *), 2);
	else
	{
		ret = ft_putcharl_fd('%', 2);
		ret += ft_putcharl_fd(c, 2);
	}
	return (ret);
}

int	ft_printf_err(const char *s, ...)
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
			ft_putcharl_fd(s[i], 2);
		i++;
	}
	va_end(vars);
	return (i + bytes);
}
