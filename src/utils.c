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

int	check_no_blank(char *s)
{
	int	i;
	int	diff_space;

	i = 0;
	diff_space = 0;
	while (s[i])
	{
		if (ft_strchr(SPACES, s[i]) != NULL)
			i++;
		if (ft_strchr(SPACES, s[i]) == NULL)
		{
			diff_space++;
			i++;
		}
	}
	if (diff_space == 0)
		return (-1);
	return (diff_space);
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
