/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:47:41 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/06/02 16:47:47 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	quote_split_setchar(char *s, char *set)
{
	int	quote;
	int	d_quote;

	quote = 0;
	d_quote = 0;
	while (*s)
	{
		if (*s == '"' && !quote && !d_quote)
			d_quote = 1;
		else if (*s == '"' && d_quote)
			d_quote = 0;
		else if (*s == '\'' && !quote && !d_quote)
			quote = 1;
		else if (*s == '\'' && quote)
			quote = 0;
		else if (ft_strchr(set, *s) && !quote && !d_quote)
			*s = -1;
		s++;
	}
	return (0);
}

t_split	*quote_split(char *s, char *set)
{
	t_split	*ret;

	quote_split_setchar(s, set);
	ret = ft_split(s, -1);
	while (*s)
	{
		if (*s == -1)
			*s = *set;
		s++;
	}
	return (ret);
}
