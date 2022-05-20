#include "../include/split_utils.h"
#include <stdio.h>

int	split_extend(t_split *split, int n)
{
	t_split	*new;
	int		i;

	if (n < split->size)
		return (0);
	new = new_split(3 * n / 2);
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
	{
		if (split_extend(split, index) < 0)
			return (-2);
		split->len++;
	}
	((void **)split->data)[index] = data;
	return (0);
}
