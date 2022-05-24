/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 15:34:24 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/05/22 02:40:39 by lnr              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	len;

	if (!dst)
		return (0);
	i = 0;
	while (i < size && dst[i])
		i++;
	j = 0;
	len = ft_strlen(dst);
	if (!src)
		return (len);
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
