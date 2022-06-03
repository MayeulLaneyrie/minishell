/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrah <bifrah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 16:26:23 by bifrah            #+#    #+#             */
/*   Updated: 2022/06/03 16:28:15 by bifrah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
**	Check si les quotes d'une string sont aux nombre pair
**	Return le nombre de caractere lu, -1 le cas echeant.
**	Ajoute a la variable globale le code d'erreur en cas d'echec.
*/
int	check_quote(char *s)
{
	int	i;
	int	quote;
	int	d_quote;

	i = 0;
	quote = 0;
	d_quote = 0;
	while (s[i])
	{
		if (s[i] == '"' && !quote && !d_quote)
			d_quote = 1;
		else if (s[i] == '"' && d_quote)
			d_quote = 0;
		else if (s[i] == '\'' && !quote && !d_quote)
			quote = 1;
		else if (s[i] == '\'' && quote)
			quote = 0;
		i++;
	}
	if (d_quote == 1 || quote == 1)
	{
		g_xt_stat = 128;
		return (write(2, "Syntax error\n", 14) * 0 - 1);
	}
	return (i);
}

/*
**	Compte le nombre de pipe dans une string donnee en parametre
**	Return le nombre de pipe ou 0 le cas echeant.
*/
int	check_pipe(char *s)
{
	int	i;
	int	nb_pipe;

	i = 0;
	nb_pipe = 0;
	while (s[i])
	{
		if (s[i] == '|')
			nb_pipe++;
		i++;
	}
	return (nb_pipe);
}

/*
**	verifie si une chaine de caractere contient seulement des espaces
**	prend en paramatre une chaine de caractere
**	return 1 s'il ya d'autre caractere que des espaces, 0 le cas echeant
*/
int	check_str(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((ft_strchr(SPACES, s[i]) != NULL))
			i++;
		else
			return (1);
	}
	return (0);
}

/*
**	verifie si une string appartenant a un "t_split"
	contient seulement des espaces
**	prend en paramatre un t_split
**	return 0 si une string contenant seulement des espaces est
	presente dans t_split, 1 autrement
*/
int	check_commands(t_split *commands)
{
	int	i;

	i = 0;
	while (i < commands->len)
	{
		if (check_str((char *)commands->data[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
