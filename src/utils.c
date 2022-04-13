#include "../include/minishell.h"

int	check_even_quote(char *s)
{
	int	d_quote;
	int	quote;
	int	i;

	i = 0;
	d_quote = 0;
	quote = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			quote++;
		if (s[i] == '"')
			d_quote++;
		i++;
	}
	if (d_quote % 2 != 0 || quote % 2 != 0)
		return (0);
	else
		return (1);
}
