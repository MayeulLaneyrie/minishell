/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 15:34:24 by mlaneyri          #+#    #+#             */
/*   Updated: 2020/11/19 16:35:45 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	while (i < size && dst[i])
		i++;
	j = 0;
	len = ft_strlen(dst);
	if (size > 0)
	{
		while (i < (size - 1) && src[j])
			dst[i++] = src[j++];
		if (size >= len)
			dst[i] = 0;
	}
	if (size < ft_strlen(dst))
		return (ft_strlen(src) + size);
	else
		return (ft_strlen(src) + len);
}
