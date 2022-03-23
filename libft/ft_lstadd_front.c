/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 21:27:09 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/03/23 03:12:38 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lstadd_front(t_list **alst, t_list *new)
{
	if (!new)
		return (NULL);
	new->next = *alst;
	*alst = new;
	return (NULL);
}
