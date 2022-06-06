/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrd_len_and_cpy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrah <bifrah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 20:18:46 by bifrah            #+#    #+#             */
/*   Updated: 2022/06/06 20:18:50 by bifrah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
**	word_len() reçoit un pointeur vers le début d'un mot
**	La fonction appelante doit garantir cette condition
**	Renvoie le nombre de char dans ce mot
**	Les quotes 'externes' ne sont pas décomptées
**	La fin de la string marque systématiquement la fin du mot
*/
int	word_len(char *s)
{
	int	ret;
	int	quote;
	int	d_quote;

	ret = 0;
	quote = 0;
	d_quote = 0;
	while (*s && (!ft_strchr(METACHAR, *s) || quote || d_quote))
	{
		if (*s == '"' && !quote && !d_quote)
			d_quote = 1;
		else if (*s == '"' && d_quote)
			d_quote = 0;
		else if (*s == '\'' && !quote && !d_quote)
			quote = 1;
		else if (*s == '\'' && quote)
			quote = 0;
		else
			ret++;
		s++;
	}
	return (ret);
}

/*
**	word_cpy() reçoit un pointeur vers le début d'un mot
**	La fonction appelante doit garantir cette condition
**	Copie les chars de ce mot de src vers dst
**	Renvoie l'index du premier char qui suit la fin du mot
**	Les quotes 'externes' ne sont pas copiées, mais sont décomptées
**	La fin de la string marque systématiquement la fin du mot
*/
int	word_cpy(char *dst, char *src)
{
	int	i;
	int	quote;
	int	d_quote;

	i = 0;
	quote = 0;
	d_quote = 0;
	while (src[i] && (!ft_strchr(METACHAR, src[i]) || quote || d_quote))
	{
		if (src[i] == '"' && !quote && !d_quote)
			d_quote = 1;
		else if (src[i] == '"' && d_quote)
			d_quote = 0;
		else if (src[i] == '\'' && !quote && !d_quote)
			quote = 1;
		else if (src[i] == '\'' && quote)
			quote = 0;
		else
		{
			*dst = src[i];
			dst++;
		}
		i++;
	}
	return (*dst = '\0', i);
}
