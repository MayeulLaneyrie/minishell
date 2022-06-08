/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrah <bifrah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 16:26:27 by bifrah            #+#    #+#             */
/*   Updated: 2022/06/08 15:52:48 by bifrah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
**	check si les operateurs sont correctement utilise
**	prend en param s : la string a checker et &i l'adresse de l'index
**	return le mode de redirection  (APPEND or TRUNC), 0 en cas d'erreur
*/
int	check_redirect_operator(char *s, int *i)
{
	int	red;

	red = 0;
	if (s[*i] && s[*i] == '>')
		red = RED_OUT;
	else if (s[*i] && s[*i] == '<')
		red = RED_IN;
	(*i)++;
	if ((red == RED_OUT && s[*i] == '<') || (red == RED_IN && s[*i] == '>'))
		return (0);
	else
	{
		if (s[*i] == '<' && red == RED_IN)
		{
			(*i)++;
			return (RED_APPEND);
		}
		if (s[*i] == '>' && red == RED_OUT)
		{
			(*i)++;
			return (RED_APPEND);
		}
		return (RED_TRUNC);
	}
}

int	here_doc_mod(t_red **tmp, t_sh *sh)
{
	int	hd_ret;

	hd_ret = 0;
	if ((*tmp)->mode == RED_APPEND && (*tmp)->in_out == RED_IN)
	{
		hd_ret = heredoc(*tmp, sh);
		if (hd_ret)
			return (free(*tmp), (hd_ret < 0) * ERR_DOC + (hd_ret > 0) * -3);
	}
	return (hd_ret);
}

int	check_redirect(char *s, t_cmd *cmd, t_list *lst, t_sh *sh)
{
	int		i;
	int		hd_ret;
	t_red	*tmp;
	char	*new_word;

	i = 0;
	tmp = malloc(sizeof(t_red));
	if (!tmp)
		return (-1);
	fill_tmp_fd_mod_inout(&tmp, s, &i, lst);
	skip_spaces(s, &i);
	if (!tmp->mode || i > (int)ft_strlen(s) || ft_strchr("<>", s[i]))
		return (free(tmp), ERR_SYNTAX);
	new_word = malloc(word_len(s + i) + 1);
	if (!new_word)
		return (free(tmp), -1);
	i += word_cpy(new_word, s + i);
	tmp->word = new_word;
	hd_ret = here_doc_mod(&tmp, sh);
	if (hd_ret != 0)
		return (hd_ret);
	if (!ft_lstadd_back(&(cmd->red), ft_lstnew(tmp)))
		return (free(tmp), (long)ft_lstclear(&cmd->red, &free) - 1);
	return (i);
}
