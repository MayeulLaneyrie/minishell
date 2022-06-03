/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 16:29:11 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/06/03 18:18:32 by lnr              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	trololo;

	trololo = 0;
	while (trololo < n)
	{
		((char *)s)[trololo] = 0;
		trololo++;
	}
}
