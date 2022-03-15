/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:38:08 by mlaneyri          #+#    #+#             */
/*   Updated: 2020/11/19 17:09:17 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	len;

	if (!*s2)
		return ((char *)s1);
	i = 0;
	len = ft_strlen(s2);
	while (s1[i] && i + len - 1 < n)
	{
		if (!ft_strncmp(s1 + i, s2, len))
			return ((char *)s1 + i);
		i++;
	}
	return (NULL);
}
