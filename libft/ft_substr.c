/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 19:01:27 by mlaneyri          #+#    #+#             */
/*   Updated: 2020/12/30 23:50:24 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ret;

	i = 0;
	while (s[i] && i < start)
		i++;
	if (i < start)
		len = 0;
	else
	{
		i = 0;
		while (s[i + start] && i < len)
			i++;
		if (i < len)
			len = i;
	}
	ret = malloc(len + 1);
	if (!ret)
		return (NULL);
	i = -1;
	while (++i < len)
		ret[i] = s[i + start];
	ret[len] = 0;
	return (ret);
}
