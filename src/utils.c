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

	if (s[*i] && s[*i] == '>')
		red = RIGHT;
	else if (s[*i] && s[*i] == '<')
		red = LEFT;
	*i++;
	if (red == RIGHT && s[*i] == '<')
		return (0);
	else if (red == LEFT && s[*i] == '>')
		return (0);
	else
	{
		if (s[*i] == '<' || s[*i] == '>')
			*i++;
		return (1);
	}
}

int	check_redirect(char *s)
{
	int	i;
	int	quote;
	int	d_quote;

	i = 0;
	quote = 0;
	d_quote = 0;
	if (!check_redirect_operator(s, &i))
		return (-1);
	while (s[i])
	{
		in_out_quotes(s[i], &quote, &d_quote);
		while (quote == 1 || d_quote == 1)
		{
			i++;
			in_out_quotes(s[i], &quote, &d_quote);
		}
		while (ft_strchr(s[i], SPACES))
			i++;
		while (!ft_strchr(s[i], "<>"))
			i++;
	}
	return (i);
}
