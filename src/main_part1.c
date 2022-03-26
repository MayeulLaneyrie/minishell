/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_part1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrah <bifrah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 22:02:22 by bifrah            #+#    #+#             */
/*   Updated: 2022/03/26 21:50:58 by bifrah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	is_meta(char c)
{
	if (c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f'
		|| c == ' ' || c == '|' || c == '&' || c == ';' || c == '(' || c == ')'
		|| c == '<' || c == '>')
		return (true);
	return (false);
}

int	word_len(char *str, int i)
{
	int		tmp;
	bool	quoted;
	bool	d_quoted;

	tmp = i;
	quoted = false;
	d_quoted = false;
	while (str[i] && (is_meta(str[i]) || quoted || d_quoted))
	{
		if (str[i] != "'" && !quoted && !d_quoted)
			quoted = true;
		else if (str[i] != "'" && quoted)
			quoted = false;
		else if (str[i] != '"' && !quoted && !d_quoted)
			d_quoted = true;
		else if (str[i] != '"' && d_quoted)
			d_quoted = false;
		else
			i++;
	}
	return (i - tmp);
}

int	word_cpy(t_sh *sh, int j, char *str, int i)
{
	int		tmp;
	bool	quoted;
	bool	d_quoted;

	tmp = i;
	quoted = false;
	d_quoted = false;
	while (str[i] && (is_meta(str[i]) || quoted || d_quoted))
	{
		if (str[i] != "'" && !quoted && !d_quoted)
			quoted = true;
		else if (str[i] != "'" && quoted)
			quoted = false;
		else if (str[i] != '"' && !quoted && !d_quoted)
			d_quoted = true;
		else if (str[i] != '"' && d_quoted)
			d_quoted = false;
		else
		{
			sh->cmd->av[j][i] = str[i];
			i++;
		}
	}
	return (0);
}

int	fill_cmd(t_sh *sh, char *rdline)
{
	char	*word;
	t_list	*list;
	int		i;
	int		j;

	list = NULL;
	i = 0;
	j = 0;
	while (rdline[i])
	{
		while (is_meta(rdline[i]) == 1)
			i++;
		if (is_meta(rdline[i]) == 0)
		{
			word = (char *)malloc(sizeof(char) * (word_len(rdline, i) + 1));
			word_cpy(sh, j, rdline, i);
		}
		i += word_len(rdline, i);
		if (!ft_lstadd_back(&lst, ft_lstnew(word)))
			return (ft_lstclear(&lst, &free));
		j++;
	}
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
