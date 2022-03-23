/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 22:54:14 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/03/23 02:40:13 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*head;

	if (!new)
		return (NULL);
	if (!*alst)
		*alst = new;
	else
	{
		head = *alst;
		while (head->next)
			head = head->next;
		head->next = new;
		new->prev = head;
	}
	return (new);
}
