/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 19:52:13 by mlaneyri          #+#    #+#             */
/*   Updated: 2020/12/31 00:09:14 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	disp[11];
	int		temp;
	int		len;

	temp = n / 10;
	len = 1 + (n < 0);
	while (temp)
	{
		len++;
		temp /= 10;
	}
	if (n < 0)
		disp[0] = '-';
	if (!n)
		disp[0] = '0';
	temp = len;
	while (n)
	{
		len--;
		disp[len] = '0' + (n % 10) * (1 - 2 * (n < 0));
		n /= 10;
	}
	write(fd, disp, temp);
}
