/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 05:13:08 by pmilner-          #+#    #+#             */
/*   Updated: 2024/10/17 00:04:57 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*calloced;

	calloced = malloc(size * nmemb);
	if (!calloced)
		return (calloced);
	ft_bzero(calloced, nmemb * size);
	return (calloced);
}
