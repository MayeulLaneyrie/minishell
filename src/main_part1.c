/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_part1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrah <bifrah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 22:02:22 by bifrah            #+#    #+#             */
/*   Updated: 2022/03/22 17:21:08 by bifrah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	fill_cmd(t_sh *sh, char *rdline)
{
	char	*tmp;
	int		i;
	int		j;
	int		k;

	tmp = (char *)malloc(sizeof(char) * (ft_strlen(rdline) + 1));
	i = 0;
	j = 0;
	k = 0;
	while (rdline[i])
	{
		if (rdline[i] == '"')
		{
			tmp[i] = '\0';
			break ;
		}
		tmp[i] = rdline[i];
		i++;
	}
	sh->cmd->av = ft_split(tmp, ' ');
	j = count_tab(sh->cmd->av);
	while (rdline[i])
	{
		tmp[k++] = rdline[i++];
		if (rdline[i] == '"')
			break ;
	}
	tmp[k] = '\0';
	
	return (0);
}

int	main_part1(t_sh *sh)
{
	char	*rdline;

	rdline = readline("Minishell MkI");
	if (rdline == NULL)
		return (NULL_RDLINE);
	if (count_quote(rdline) == -1)
		return (WRONG_NB_QUOTE);
	else if (rdline == "")
	{
		sh->cmd = new_cmd();
		sh->cmd->av = "";
		return (BLANK_RDLINE);
	}
	else
	{
		sh->cmd = new_cmd();
		if (find_quote(rdline) == 0)
		{
			sh->cmd->av = ft_split(rdline, ' ');
			sh->cmd->ac = ac_of_av(sh->cmd->av);
		}
		else
			fill_cmd(sh, rdline);
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
*/