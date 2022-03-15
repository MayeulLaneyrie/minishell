/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 16:56:08 by mlaneyri          #+#    #+#             */
/*   Updated: 2020/12/31 00:28:53 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_fnv3(int n)
{
	int	ret;

	ret = 1 + (n < 0);
	n /= 10;
	while (n)
	{
		ret++;
		n /= 10;
	}
	return (ret);
}

char	*ft_itoa(int n)
{
	char	*ret;
	size_t	len;

	len = ft_fnv3(n);
	ret = malloc(len + 1);
	if (!ret)
		return (NULL);
	ret[len] = '\0';
	if (n < 0)
		ret[0] = '-';
	if (!n)
		ret[0] = '0';
	while (n)
	{
		len--;
		ret[len] = '0' + (n % 10) * (1 - 2 * (n < 0));
		n /= 10;
	}
	return (ret);
}
