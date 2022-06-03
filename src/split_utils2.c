/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrah <bifrah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:19:19 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/06/03 16:27:10 by bifrah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/split_utils.h"

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
