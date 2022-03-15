/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 19:11:47 by mlaneyri          #+#    #+#             */
/*   Updated: 2020/12/30 23:54:27 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	char	*ret;

	len1 = 0;
	while (s1[len1])
		len1++;
	len2 = 0;
	while (s2[len2])
		len2++;
	ret = malloc(len1 + len2 + 1);
	if (!ret)
		return (NULL);
	i = 0;
	while (s1[++i - 1])
		ret[i - 1] = s1[i - 1];
	while (s2[i - len1 - 1])
	{
		ret[i - 1] = s2[i - len1 - 1];
		i++;
	}
	ret[len1 + len2] = 0;
	return (ret);
}
