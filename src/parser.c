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

/*
**	cut_words() prend en paramètre une chaine de caractères, et renvoie
**	un t_split contenant les mots qu'elle contient, découpés selon les
**	règles de quoting de bash.
*/
int	cut_words(char *s, t_cmd *cmd, t_split	**ret)
{
	int		l;
	char	*w;
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
			if (!jump)
				l = check_redirect(s, cmd, tmp);
			else
				l = check_redirect(s, cmd, NULL);
			if (l == -1)
				return (ft_lstclear(&tmp, &free), -1);
			if (l == -2)
				return (ft_lstclear(&tmp, &free), -4);
			s += l;
		}
		else
		{
			l = word_len(s);
			w = malloc(l + 1);
			if (!w)
				return (ft_lstclear(&tmp, &free), -1);
			s += word_cpy(w, s);
			if (!ft_lstadd_back(&tmp, ft_lstnew(w)))
				return (ft_lstclear(&tmp, &free), -1);
		}
	}
	(*ret) = list_to_split(&tmp);
	if (!(*ret))
		return (ft_lstclear(&tmp, &free), -1);
	return (0);
}

int	parse_cmd(char *s, t_sh *sh)
{
	t_split	*words;
	t_split	*commands;
	int		i;

	commands = quote_split(s, "|");
	if (!commands)
		return (-1);
	sh->pipeline = new_split(commands->len);
	i = -1;
	while (++i < commands->len)
	{
		sh->pipeline->data[i] = new_cmd();
		if (!sh->pipeline->data[i])
			return (-2);
		if (cut_words((char *)commands->data[i],
				(t_cmd *)sh->pipeline->data[i], &words) == -4)
			return (free(sh->pipeline->data[i]),
				(unsigned long long)del_split(commands, &ft_free) - 4);
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

/*
**	Parse le retour de readline :
**	et stock les tokens dans un char ** (sh.pipeline.data.av)
*/
int	main_part1(t_sh *sh)
{
	char	*s;
	int		i;
	int		parse_ret;

	while (1)
	{
		if (isatty(0))
			s = readline("$ ");
		else
			get_next_line(&s);
		if (!s)
			return (write(2, "exit\n", 5) * 0 + 1);
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
	if (parse_ret != 0 && parse_ret != -4)
		return ((unsigned long)ft_free((void *)s) + 1);
	if (parse_ret == -4)
		return (write(2, "Syntax error\n", 13),
			(unsigned long)ft_free((void *)s) - 4);
	return (free(s), 0);
}
