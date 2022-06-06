/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrah <bifrah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 16:26:06 by bifrah            #+#    #+#             */
/*   Updated: 2022/06/06 20:15:37 by bifrah           ###   ########.fr       */
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
		return (ft_lstclear(tmp, &free), -1);
	*s += word_cpy(w, *s);
	if (!ft_lstadd_back(tmp, ft_lstnew(w)))
		return (ft_lstclear(tmp, &free), -1);
	return (0);
}

/*
**	cut_words() prend en paramètre une chaine de caractères, et renvoie
**	un t_split contenant les mots qu'elle contient, découpés selon les
**	règles de quoting de bash.
*/
int	cut_words(char *s, t_cmd *cmd, t_split	**ret)
{
	int		l;
	t_list	*tmp;
	int		jump;

	tmp = NULL;
	while (*s)
	{
		jump = 0;
		while (*s && ft_strchr(SPACES, *s))
		{
			jump = 1;
			s++;
		}
		if (!*s)
			break ;
		if (ft_strchr("<>", *s))
		{
			l = check_redirect(s, cmd, tmp, jump);
			if (l < 0)
				return (ft_lstclear(&tmp, &free), l);
			s += l;
		}
		else
			no_redirect(&s, &tmp);
	}
	(*ret) = list_to_split(&tmp);
	if (!(*ret))
		return (ft_lstclear(&tmp, &free), -1);
	return (0);
}

/*
**	Parse le retour de readline :
**	et stock les tokens dans un char ** (sh.pipeline.data.av)
*/
int	parse_cmd(char *s, t_sh *sh)
{
	t_split	*words;
	t_split	*commands;
	int		i;
	int		ctwrdret;

	commands = quote_split(s, "|");
	if (!commands)
		return (-1);
	if (!check_commands(commands))
		return (ERR_SYNTAX);
	sh->pipeline = new_split(commands->len);
	i = -1;
	while (++i < commands->len)
	{
		sh->pipeline->data[i] = new_cmd();
		if (!sh->pipeline->data[i])
			return (-2);
		ctwrdret = cut_words((char *)commands->data[i],
				(t_cmd *)sh->pipeline->data[i], &words);
		if (ctwrdret < -2)
			return (free(sh->pipeline->data[i]),
				(unsigned long long)del_split(commands, &ft_free) + ctwrdret);
		if (!words)
			return (free(sh->pipeline->data[i]),
				(unsigned long long)del_split(commands, &ft_free) - 3);
		((t_cmd *)sh->pipeline->data[i])->av = (char **)words->data;
		((t_cmd *)sh->pipeline->data[i])->ac = words->len;
		sh->pipeline->len++;
		free(words);
	}
	del_split(commands, &ft_free);
	return (0);
}

int	main_part1(t_sh *sh)
{
	char	*s;
	int		i;
	int		parse_ret;

	while (1)
	{
		if (isatty(0))
		{
			sig_init(SIGINT, sa_main_handler);
			s = readline("$ ");
			sig_init(SIGINT, SIG_IGN);
		}
		else
		{
			i = get_next_line(&s);
			if (i < 1)
				return ((long)ft_free(s) + 1);
		}
		if (!s)
			return (write(2, "exit\n", 5) * 0 - 1);
		i = -1;
		while (ft_strchr(SPACES, s[++i]) && s[i])
			;
		if (*s && s[i])
		{
			add_history(s);
			if (check_quote(s) != -1)
				break ;
		}
		free(s);
	}
	s = all_dollar_subst(sh->env, s);
	if (!s)
		return (1);
	parse_ret = parse_cmd(s, sh);
	if (parse_ret == ERR_SYNTAX)
		return (write(2, "Syntax error\n", 13),
			(unsigned long)ft_free((void *)s) ERR_SYNTAX);
	if (parse_ret == -6)
		return ((unsigned long)ft_free((void *)s) ERR_DOC);
	if (parse_ret != 0)
		return ((unsigned long)ft_free((void *)s) + 1);
	return (free(s), 0);
}
