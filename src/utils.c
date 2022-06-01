#include "../include/minishell.h"

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

int	check_redirect(char *s, t_cmd *cmd)
{
	int		i;
	int		quote;
	int		d_quote;
	int		mode;
	t_red	*tmp;

	i = 0;
	quote = 0;
	d_quote = 0;
	tmp->mode = check_redirect_operator(s, &i);
	if (!tmp->mode)
		return (-1);
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
			i++;
		
		if (!ft_lstadd_back(cmd->red, ft_lstnew(tmp)))
			return (ft_lstclear(&cmd, &free));
	}
	return (i);
}
