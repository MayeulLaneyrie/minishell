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
	*dst = '\0';
	return (i);
}

/*
**	cut_words() prend en paramètre une chaine de caractères, et renvoie
**	un t_split contenant les mots qu'elle contient, découpés selon les
**	règles de quoting de bash.
*/
t_split	*cut_words(char *s)
{
	int		l;
	char	*w;
	t_list	*tmp;
	t_split	*ret;

	tmp = NULL;
	while (*s)
	{
		while (*s && ft_strchr(METACHAR, *s))
			s++;
		if (!*s)
			break ;
		l = word_len(s);
		w = malloc(l + 1);
		if (!w)
			return (ft_lstclear(&tmp, &free));
		s += word_cpy(w, s);
		if (!ft_lstadd_back(&tmp, ft_lstnew(w)))
			return (ft_lstclear(&tmp, &free));
	}
	ret = list_to_split(&tmp);
	if (!ret)
		return (ft_lstclear(&tmp, &free));
	return (ret);
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
		words = cut_words((char *)commands->data[i]);
		if (!words)
			return ((unsigned long long)del_split(commands, &ft_free) - 3);
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

	while (1)
	{
		s = readline("$ ");
		if (!s)
		{
			write(2, "exit\n", 5);
			return (1);
		}
		if (*s)
		{
			add_history(s);
			if (check_quote(s) != -1)
				break ;
		}
		free(s);
	}
	if (parse_cmd(s, sh))
		return ((unsigned long)ft_free((void *)s) + 1);
	free(s);
	return (0);
}
