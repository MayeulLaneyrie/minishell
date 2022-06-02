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

int	check_redir(char *s)
{
	int	i;
	int	nb_redir;

	i = 0;
	nb_redir = 0;
	while (s[i])
	{
		if (s[i] == '>' || s[i] == '<')
			nb_redir++;
		i++;
	}
	return (nb_redir);
}

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
	if (red == RED_OUT && s[*i] == '<')
		return (0);
	else if (red == RED_IN && s[*i] == '>')
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

int	set_red_fd(int in_out, t_list *lst)
{
	t_list			*head;
	int				i;
	char			*s;
	unsigned long	ret;

	head = ft_lstlast(lst);
	if (!head)
		return (in_out == RED_OUT);
	s = head->data;
	i = -1;
	while (s[++i])
		if (!ft_isdigit(s[i]))
			break;
	if (s[i] || i > 10)
		return (in_out == RED_OUT);
	ret = ft_atoi(s);
	if (ret > 2147483647)
		return (in_out == RED_OUT);
	free(s);
	if (head->next)
		head->next->prev = NULL;
	if (head->prev)
		head->prev->next = NULL;
	free(head);
	return (ret);
}

int	check_redirect(char *s, t_cmd *cmd, t_list *lst)
{
	int		i;
	int		quote;
	int		d_quote;
	t_red	*tmp;
	char	*new_word;
	int		j;

	i = 0;
	j = 0;
	quote = 0;
	d_quote = 0;
	tmp = malloc(sizeof(t_red));
	if (s[i] == '>')
		tmp->in_out = RED_OUT;
	else if (s[i] == '<')
		tmp->in_out = RED_IN;
	tmp->mode = check_redirect_operator(s, &i);
	if (!tmp->mode)
		return (-1);
	tmp->fd = set_red_fd(tmp->in_out, lst);
	/*
	in_out_quotes(s[i], &quote, &d_quote);
	while (quote == 1 || d_quote == 1)
	{
		i++;
		in_out_quotes(s[i], &quote, &d_quote);
	}
	*/
	while (ft_strchr(SPACES, s[i]))
		i++;
	if (ft_strchr("<>", s[i]))
		return (-1);
	new_word = malloc(word_len(s + i) + 1);
	if (!new_word)
		return (-1);
	i += word_cpy(new_word, s + i);
	tmp->word = new_word;
	if (tmp->mode == RED_APPEND && tmp->in_out == RED_IN && heredoc(tmp) < 0)
		return (-1);
	if (!ft_lstadd_back(&(cmd->red), ft_lstnew(tmp)))
		return ((long)ft_lstclear(&cmd->red, &free) - 1);
	return (i);
}
