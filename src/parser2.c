/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrah <bifrah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 16:26:06 by bifrah            #+#    #+#             */
/*   Updated: 2022/06/08 15:56:35 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	no_redirect(char **s, t_list **tmp)
{
	int		l;
	char	*w;

	l = word_len(*s);
	w = malloc(l + 1);
	if (!w)
		return (-1);
	*s += word_cpy(w, *s);
	if (!ft_lstadd_back(tmp, ft_lstnew(w)))
		return (-1);
	return (0);
}

/*
**	cut_words() prend en paramètre une chaine de caractères, et renvoie
**	un t_split contenant les mots qu'elle contient, découpés selon les
**	règles de quoting de bash.
*/

int	skip_spaces_adress(char **s)
{
	int	jump;

	jump = 0;
	while (**s && ft_strchr(SPACES, **s))
	{
		jump = 1;
		(*s)++;
	}
	if (jump == 1)
		return (1);
	else
		return (0);
}

int	get_next_thing(char **s, t_cmd *cmd, t_sh *sh, t_list **tmp)
{
	int	jump;
	int	l;

	jump = skip_spaces_adress(s);
	if (!**s)
		return (-42);
	if (ft_strchr("<>", **s))
	{
		if (!jump)
			l = check_redirect(*s, cmd, *tmp, sh);
		else
			l = check_redirect(*s, cmd, NULL, sh);
		if (l < 0)
			return (ft_lstclear(tmp, &free), l);
		*s += l;
	}
	else
		if (no_redirect(s, tmp) == -1)
			return (ft_lstclear(tmp, &free), -1);
	return (0);
}

int	cut_words(char *s, t_cmd *cmd, t_split **ret, t_sh *sh)
{
	int		l;
	t_list	*tmp;

	tmp = NULL;
	while (*s)
	{
		l = get_next_thing(&s, cmd, sh, &tmp);
		if (l == -42)
			break ;
		if (l)
			return (l);
	}
	if (!tmp)
		return (ERR_SYNTAX + (long)ft_lstclear(&(cmd->red), &del_red));
	*ret = list_to_split(&tmp);
	if (!*ret)
		return (ft_lstclear(&tmp, &free), -1);
	return (0);
}

int	while_of_parse_cmd(t_sh *sh, int i, t_split **commands, t_split **words)
{
	int	ret;

	sh->pipeline->data[i] = new_cmd();
	if (!sh->pipeline->data[i])
		return (-2);
	ret = cut_words((char *)((*commands)->data[i]),
			(t_cmd *)sh->pipeline->data[i], words, sh);
	if (ret < -2)
		return (ret);
	if (!*words)
		return (-3);
	((t_cmd *)sh->pipeline->data[i])->av = (char **)(*words)->data;
	((t_cmd *)sh->pipeline->data[i])->ac = (*words)->len;
	sh->pipeline->len++;
	free(*words);
	return (0);
}
