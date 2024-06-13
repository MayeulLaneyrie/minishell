/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrah <bifrah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 16:26:06 by bifrah            #+#    #+#             */
/*   Updated: 2023/03/28 17:30:10 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
**	Parse le retour de readline :
**	et stock les tokens dans un char ** (sh.pipeline.data.av)
*/
int	parse_cmd(char *s, t_sh *sh)
{
	t_split	*words;
	t_split	*commands;
	int		i;
	int		ret;

	commands = quote_split(s, "|");
	if (!commands)
		return (-1);
	if (!check_commands(commands))
		return (ERR_SYNTAX);
	sh->pipeline = new_split(commands->len);
	if (!sh->pipeline)
		return (-1);
	i = -1;
	while (++i < commands->len)
	{
		ret = while_of_parse_cmd(sh, i, &commands, &words);
		if (ret == -2)
			return (-2);
		if (ret < -2)
			return (free(sh->pipeline->data[i]),
				(unsigned long long)del_split(commands, &ft_free) + ret);
	}
	del_split(commands, &ft_free);
	return (0);
}

int	supra_readline(char **s)
{
	int	i;

	if (isatty(0))
	{
		sig_init(SIGINT, sa_main_handler);
		*s = readline("$ ");
		sig_init(SIGINT, SIG_IGN);
	}
	else
	{
		i = get_next_line(s);
		if (i < 1)
			return ((long)ft_free(*s) + 1);
	}
	return (0);
}

int	super_readline(char **s)
{
	int	i;

	while (1)
	{
		i = supra_readline(s);
		if (i)
			return (i);
		if (!*s)
			return (write(2, "exit\n", 5) * 0 - 1);
		i = -1;
		while (ft_strchr(SPACES, *s[++i]) && *s[i])
			;
		if (**s && *s[i])
		{
			add_history(*s);
			if (check_quote(*s) != -1)
				break ;
		}
		free(*s);
	}
	return (0);
}

int	main_part1(t_sh *sh)
{
	char	*s;
	int		i;
	int		parse_ret;

	i = super_readline(&s);
	if (i)
		return (i);
	s = all_dollar_subst(sh->env, s);
	if (!s)
		return (1);
	parse_ret = parse_cmd(s, sh);
	if (parse_ret == ERR_SYNTAX)
		return (write(2, "Syntax error\n", 13),
			(long)ft_free((void *)s) ERR_SYNTAX + 0 * (g_xt_stat = 2));
	if (parse_ret == -6)
		return ((long)ft_free((void *)s) ERR_DOC);
	if (parse_ret != 0)
		return ((long)ft_free((void *)s) + parse_ret);
	return (free(s), 0);
}
