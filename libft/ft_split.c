/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 14:16:52 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/06/08 15:06:56 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_splitsize(char const *s, char c)
{
	int	ret;

	ret = 1;
	while (*s)
	{
		if (*s == c)
			ret++;
		s++;
	}
	return (ret);
}

static int	ft_splitfill(char **ret, char const *s, char c)
{
	int		i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	ret[0] = malloc(i + 1);
	if (!ret[0])
		return (-1);
	i = 0;
	while (*s != c && *s)
	{
		ret[0][i] = *s;
		s++;
		i++;
	}
	ret[0][i] = '\0';
	if (!*s)
		return (0);
	s++;
	if (!ft_splitfill(&ret[1], s, c))
		return (0);
	free(ret[0]);
	return (-1);
}

t_split	*ft_split(char const *s, char c)
{
	t_split	*ret;
	int		size;

	size = ft_splitsize(s, c);
	ret = new_split(size);
	if (!ret)
		return (NULL);
	if (ft_splitfill((char **)ret->data, s, c))
		return (del_split(ret, &ft_free));
	ret->len = size;
	return (ret);
}
