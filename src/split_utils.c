/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrah <bifrah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:49:11 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/06/03 16:27:15 by bifrah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/split_utils.h"

t_split	*new_split(int n)
{
	t_split	*ret;
	int		i;

	ret = malloc(sizeof(t_split));
	if (!ret)
		return (NULL);
	ret->data = malloc((n + 1) * sizeof(void *));
	if (!ret->data)
	{
		free(ret);
		return (NULL);
	}
	i = -1;
	while (++i < n + 1)
		ret->data[i] = NULL;
	ret->size = n;
	ret->len = 0;
	return (ret);
}

void	*del_split(t_split *split, void *(*del)(void *))
{
	int	i;

	if (!split)
		return (0);
	i = -1;
	while (++i < split->len)
		del(split->data[i]);
	free(split->data);
	free(split);
	return (0);
}

t_split	*list_to_split(t_list **lst)
{
	int		n;
	t_list	*cpy;
	t_split	*ret;

	if (!lst || !*lst)
		return (NULL);
	n = ft_lstsize(*lst);
	ret = new_split(n);
	if (!ret)
		return (NULL);
	while (ret->len < n)
	{
		(ret->data)[ret->len] = (*lst)->data;
		ret->len++;
		cpy = *lst;
		*lst = (*lst)->next;
		free(cpy);
	}
	*lst = NULL;
	return (ret);
}

void	nothing(void *ptr)
{
	(void)ptr;
}

t_list	*split_to_list(t_split **split)
{
	int		i;
	t_list	*ret;
	t_list	*new;

	ret = NULL;
	i = -1;
	while (++i < (*split)->len)
	{
		new = ft_lstnew((*split)->data);
		if (!new)
		{
			ft_lstclear(&ret, &nothing);
			return (NULL);
		}
		ft_lstadd_back(&ret, new);
	}
	free((*split)->data);
	free(*split);
	*split = NULL;
	return (ret);
}
