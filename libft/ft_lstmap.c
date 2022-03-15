/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 23:47:01 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/03/15 16:46:50 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_r(t_list *l1, t_list **l2, void *(*f)(void *), void (*d)(void *))
{
	void	*new_data;

	if (!l1)
		return (0);
	new_data = f(l1->data);
	if (!new_data)
		return (-1);
	*l2 = ft_lstnew(new_data);
	if (!*l2)
	{
		free(new_data);
		return (-1);
	}
	if (!ft_r(l1->next, &((*l2)->next), f, d))
		return (0);
	else
	{
		ft_lstdelone(*l2, d);
		return (-1);
	}
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ret;

	ret = NULL;
	if (!ft_r(lst, &ret, f, del))
		return (ret);
	else
		return (NULL);
}
