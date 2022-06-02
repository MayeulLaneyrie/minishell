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

t_list	check_redirect(char *s, t_cmd *cmd)
{
	int		i;
	int		quote;
	int		d_quote;
	t_red	*tmp;
	char	new_word[1000];
	int		j;

	i = 0;
	j = 0;
	quote = 0;
	d_quote = 0;
	tmp = malloc(sizeof(t_red) + 1);
	tmp->mode = check_redirect_operator(s, &i);
	if (s[i] == '>')
		tmp->in_out = RED_OUT;
	else if (s[i] == '<')
		tmp->in_out = RED_IN;
	while (s[i])
	{
		in_out_quotes(s[i], &quote, &d_quote);
		while (quote == 1 || d_quote == 1)
		{
			i++;
			in_out_quotes(s[i], &quote, &d_quote);
		}
		while (ft_strchr(SPACES, s[i]))
			i++;
		while (!ft_strchr("<>", s[i]))
			new_word[j++] = s[i++];
		new_word[j] = '\0';
		tmp->word = ft_strdup(new_word);
		if (!ft_lstadd_back(&cmd->red, ft_lstnew(tmp)))
		{
			ft_lstclear(&cmd->red, &free);
			return (NULL);
		}
		while (ft_strchr(SPACES, s[i]))
			i++;
	}
	return (NULL);
}
