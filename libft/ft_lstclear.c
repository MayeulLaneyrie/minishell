/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 23:10:23 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/03/23 03:13:15 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_lstclearall(t_list *lst, void (*del)(void *))
{
	t_list	*cpy;
	t_list	*cpy1;

	cpy = lst;
	cpy1 = cpy->next;
	while (cpy1)
	{
		ft_lstdelone(cpy1, del);
		cpy = cpy1;
		cpy1 = cpy1->next;
		free(cpy);
	}
	cpy = lst;
	cpy1 = cpy->prev;
	while (cpy1)
	{
		ft_lstdelone(cpy1, del);
		cpy = cpy1;
		cpy1 = cpy1->prev;
		free(cpy);
	}
}

void	*ft_lstclear(t_list **lst, void (*del)(void *))
{
	if (!*lst)
		return (NULL);
	ft_lstclearall(*lst, del);
	ft_lstdelone(*lst, del);
	free(*lst);
	*lst = NULL;
	return (NULL);
}
