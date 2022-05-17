#include "../include/minishell.h"

int	parse_cmd(char *s, t_sh *sh)
{
	t_split	*words;
	t_split	*commands;
	int		i;

	commands = quote_split(s, "|");
	if (!commands)
		return (-1);
	sh->pipeline = new_split(commands->len);
	i = -1;
	while (++i < commands->len)
	{
		sh->pipeline->data[i] = new_cmd();
		if (!sh->pipeline->data[i])
			return (-2);
		words = quote_split((char *)commands->data[i], METACHAR);
		if (!words)
			return ((unsigned long long)del_split(commands, &ft_free) - 3);
		((t_cmd *)sh->pipeline->data[i])->av = (char **)words->data;
		((t_cmd *)sh->pipeline->data[i])->ac = words->len;
		sh->pipeline->len++;
		free(words);
	}
	del_split(commands, &ft_free);
	return (0);
}

/*
**	Parse le retour de readline :
**	et stock les tokens dans un char ** (sh.pipeline.data.av)
*/
int	main_part1(t_sh *sh)
{
	char	*s;

	while (1)
	{
		s = readline("$ ");
		if (!s)
		{
			write(2, "exit\n", 5);
			return (1);
		}
		if (*s)
		{
			add_history(s);
			if (check_quote(s) != -1)
				break ;
		}
		free(s);
	}
	if (parse_cmd(s, sh))
		return ((unsigned long)ft_free((void *)s) + 1);
	free(s);
	return (0);
}
