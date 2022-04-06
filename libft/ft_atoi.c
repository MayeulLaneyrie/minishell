/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 17:11:37 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/04/05 04:12:47 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	unsigned long long int	ret;
	int						sgn;

	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	sgn = 1;
	if (*str == '-')
		sgn = -1;
	if (*str == '-' || *str == '+')
		str++;
	ret = 0;
	while (*str >= '0' && *str <= '9')
	{
		ret = ret * 10 + *str - '0';
		str++;
	}
	return (sgn * ret);
}
