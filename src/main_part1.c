/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_part1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrah <bifrah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 22:02:22 by bifrah            #+#    #+#             */
/*   Updated: 2022/03/18 01:02:50 by bifrah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ac_of_av(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}

int	check_are_close(char *rdline)
{
	char	*tmp1;
	char	*tmp2;
	int		i;

	i = 0;
	tmp1 = ft_strnstr(rdline, "'", 1);
	tmp2 = tmp1;
	while (1)
	{
		if (tmp2[i] == "'")
		{
			tmp2[i] = '\0';
			break ;
		}
		else
			i++;
		if (tmp2[i] == '\0')
			return (1);
	}
	return (0);
}

int	take_quote(char *rdline)
{

}

int	find_quote(char *rdline)
{
	if (ft_strnstr(rdline, "'", 1) == NULL
		&& ft_strnstr(rdline, '"', 1) == NULL)
		return (0);
	else
		return (1);
}

int	main_part1(t_sh *sh)
{
	char	*rdline;

	rdline = readline("Minishell MkI");
	if (rdline == NULL)
		return (NULL_RDLINE);
	else if (rdline == "")
		return (BLANK_RDLINE);
	else
	{
		sh->cmd = new_cmd();
		if (find_quote(rdline) == 0)
		{
			sh->cmd->av = ft_split(rdline, ' ');
			sh->cmd->ac = ac_of_av(sh->cmd->av);
		}
		else
		{
			if (check_are_close(rdline) == 0)
			{
				take_quote(rdline);
			}
			else
			{
				sh->cmd->av = ft_split(rdline, ' ');
				sh->cmd->ac = ac_of_av(sh->cmd->av);
			}
		}
	}
	return (0);
}

/*
** TO DO :
**
**- faire une recuperation de ce qu'il y a dans les quote (fct : take_quote)
**- le comparer avec rdline pour l'extraire et le stocker dans un char *
**sans split les espace
**- faire de meme pour double quote
**- verifier si dans les quote ou dquote extraite il n'y a pas d'autre quotes
**- (penser a compter au tout debut combien il y a de quote pour voir si elles sont imbrique)
*/