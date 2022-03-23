/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 23:00:13 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/03/23 02:41:06 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return (NULL);
	if (lst->data)
		del(lst->data);
	free(lst);
	return (NULL);
}
