/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 06:47:17 by pmilner-          #+#    #+#             */
/*   Updated: 2024/10/17 23:28:17 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*clear(t_list *lst, void *content, void (*del)(void *))
{
	del(content);
	ft_lstclear(&lst, del);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*retstart;
	t_list	*temp;
	void	*content;

	retstart = NULL;
	content = NULL;
	while (lst)
	{
		content = f(lst->content);
		if (!content)
			return (clear(retstart, content, del));
		temp = ft_lstnew(content);
		if (!temp)
			return (clear(retstart, content, del));
		ft_lstadd_back(&retstart, temp);
		lst = lst->next;
	}
	return (retstart);
}
