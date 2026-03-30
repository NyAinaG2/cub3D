/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrrand <andrrand@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:28:39 by andrrand          #+#    #+#             */
/*   Updated: 2025/03/15 08:37:28 by andrrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*start;
	t_list	*out;

	if (!lst || !f || !del)
		return (NULL);
	out = ft_lstnew(f(lst->content));
	if (!out)
		return (NULL);
	start = out;
	while (lst->next)
	{
		lst = lst->next;
		out->next = ft_lstnew(f(lst->content));
		if (!out->next)
		{
			ft_lstclear(&start, del);
			return (NULL);
		}
		out = out->next;
	}
	return (start);
}
