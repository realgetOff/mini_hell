/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 06:29:21 by pmilner-          #+#    #+#             */
/*   Updated: 2024/10/17 22:19:49 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*tlst;

	tlst = *lst;
	while (tlst)
	{
		temp = tlst->next;
		ft_lstdelone(tlst, del);
		tlst = temp;
	}
	*lst = NULL;
}
