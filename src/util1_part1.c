#include "../include/minishell.h"

int	count_quote(char *rdline)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (rdline[i])
	{
		if (rdline[i] == '"')
			count++;
		i++;
	}
	if (count % 2 == 1)
		return (-1);
	i = 0;
	count = 0;
	while (rdline[i])
	{
		if (rdline[i] == '\'')
			count++;
		i++;
	}
	if (count % 2 == 1)
		return (-1);
	return (0);
}

bool	find_d_quote(char *rdline)
{
	int	i;

	i = 0;
	while (rdline[i])
	{
		if (rdline[i] == '\"')
			return (true);
		i++;
	}
	return (false);
}

bool	find_quote(char *rdline)
{
	int	i;

	i = 0;
	while (rdline[i])
	{
		if (rdline[i] == '\'')
			return (true);
		i++;
	}
	return (false);
}

bool	is_meta(char c)
{
	if (c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f'
		|| c == ' ' || c == '|' || c == '&' || c == ';' || c == '(' || c == ')'
		|| c == '<' || c == '>')
		return (true);
	return (false);
}

bool	is_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f' || c == ' ')
		return (true);
	return (false);
}
