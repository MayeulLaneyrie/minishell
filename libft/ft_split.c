/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 14:16:52 by mlaneyri          #+#    #+#             */
/*   Updated: 2020/12/31 00:08:27 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_splitsize(char const *s, char c)
{
	while (*s && *s == c)
		s++;
	if (!*s)
		return (0);
	while (*s && *s != c)
		s++;
	if (!*s)
		return (1);
	return (1 + ft_splitsize(s, c));
}

static int	ft_splitfill(char **ret, char const *s, char c)
{
	int		i;

	while (*s && *s == c)
		s++;
	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (!i)
		return (0);
	ret[0] = malloc(i + 1);
	if (!ret[0])
		return (-1);
	i = 0;
	while (*s && *s != c)
	{
		ret[0][i] = *s;
		s++;
		i++;
	}
	ret[0][i] = 0;
	if (!ft_splitfill(&ret[1], s, c))
		return (0);
	free(ret[0]);
	return (-1);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	int		size;

	size = ft_splitsize(s, c);
	ret = malloc(sizeof(char *) * (size + 1));
	if (!ret)
		return (NULL);
	if (ft_splitfill(ret, s, c))
	{
		free(ret);
		return (NULL);
	}
	ret[size] = 0;
	return (ret);
}
