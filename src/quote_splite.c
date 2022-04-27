#include "../include/minishell.h"

// Quote split, le splite ultime, qui respecte vos règles de quoting !

int	quote_split_setchar(char *s, char c)
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
		else if (*s == c)
			*s = -1;
		s++;
	}
	return (0);
}

int	quote_split_cleanchar(char *s, char c)
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
		else if (*s == -1)
			*s = c;
		s++;
	}
	return (0);
}


t_split	*quote_split(char *s, char c)
{
	t_split *ret;

	quote_split_setchar(s, c);
	ret = ft_split(s, -1);
	quote_split_cleanchar(s, c);
	return (ret);
}
