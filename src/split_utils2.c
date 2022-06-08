/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 16:19:16 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/06/08 14:47:35 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/split_utils.h"
#include <stdio.h>

int	split_extend(t_split *split, int n)
{
	t_split	*new;
	int		i;

	if (n < split->size)
		return (0);
	new = new_split(1 + 3 * n / 2);
	if (!new)
		return (-1);
	i = -1;
	while (++i < split->len)
	{
		new->data[i] = split->data[i];
		new->len++;
	}
	free(split->data);
	split->data = new->data;
	split->len = new->len;
	split->size = new->size;
	free(new);
	return (0);
}

int	split_push(t_split *split, void *data, int index)
{
	if (index > split->len || index < 0)
		return (-1);
	if (index == split->size)
		if (split_extend(split, index) < 0)
			return (-2);
	if (index == split->len)
		split->len++;
	((void **)split->data)[index] = data;
	return (0);
}
