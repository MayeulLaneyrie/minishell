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
		if (rdline[i] == "'")
			count++;
		i++;
	}
	if (count % 2 == 1)
		return (-1);
	return (0);
}

int	find_quote(char *rdline)
{
	if (ft_strnstr(rdline, "'", 1) == NULL
		&& ft_strnstr(rdline, '"', 1) == NULL)
		return (0);
	else
		return (1);
}

int	ac_of_av(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}
