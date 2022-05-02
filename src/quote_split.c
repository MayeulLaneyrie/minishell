#include "../include/minishell.h"

// Quote split, le split ultime, qui respecte vos règles de quoting !

int	quote_split_setchar(char *s, char c)
{
	int	quote;
	int	d_quote;

	quote = 0;
	d_quote = 0;
	while (*s)
	{
		if (*s == '"' && !quote && !d_quote)
			d_quote = 1;
		else if (*s == '"' && d_quote)
			d_quote = 0;
		else if (*s == '\'' && !quote && !d_quote)
			quote = 1;
		else if (*s == '\'' && quote)
			quote = 0;
		else if (*s == c && !quote && !d_quote)
			*s = -1;
		s++;
	}
	return (0);
}

t_split	*quote_split(char *s, char c)
{
	t_split	*ret;

	quote_split_setchar(s, c);
	ret = ft_split(s, -1);
	while (*s)
	{
		if (*s == -1)
			*s = c;
		s++;
	}
	return (ret);
}
