#include "../include/minishell.h"

int	jump_noslash(char *s, int gap)
{
	int	i;

	i = 0;
	while (s[i + gap] && s[i + gap] != '/')
	{
		s[i] = s[i + gap];
		i++;
	}
	return (i);
}

int	remove_dot(char *s)
{
	int	gap;

	gap = 0;
	while (s[gap])
	{
		while (s[gap] && s[gap] == '/')
		{
			*s = s[gap];
			s++;
		}
		if (s[gap] == '.' && (s[gap + 1] == '/' || !s[gap + 1]))
			gap += 2;
		else
			s += jump_noslash(s, gap);
	}
	*s = '\0';
	return (0);
}

int	cancel_dotdot(char *s, int n)
{
	int	ret;
	int	i;

	ret = 0;
	i = n;
	while (i && s[--i] == '/')
		ret++;
	if (!i && s[0] == '/')
		return (ret - 1);
	if (!i)
		return (0);
	while (i && s[i--] != '/')
		ret++;
	return (ret);
}

int	remove_dotdot(char *s)
{
	int	i;
	int	gap;
	int	n;

	i = 0;
	gap = 0;
	while (s[i + gap])
	{
		while (s[i + gap] && s[i + gap] == '/')
		{
			s[i] = s[i + gap];
			i++;
		}
		if (s[i + gap] == '.' && s[i + gap + 1] == '.'
			&& (s[i + gap + 2] == '/' || !s[i + gap + 2]))
		{
			n = cancel_dotdot(s, i);
			gap += 3 + n;
			i -= n;
			while (s[i + gap] && s [i + gap] == '/')
				gap++;
		}
		else
			i += jump_noslash(s + i, gap);
	}
	return (s[i] = 0);
}

int	remove_slashslash(char *s)
{
	int	gap;

	gap = 0;
	while (s[gap])
	{
		s += jump_noslash(s, gap);
		if (!*s)
			break ;
		s++;
		while (s[gap] && s[gap] == '/')
			gap++;
	}
	*s = '\0';
	return (0);
}

int	make_canonical(char *s)
{
	remove_dot(s);
	remove_dotdot(s);
	remove_slashslash(s);
	return (s[0]);
}

int	bi_cd(t_sh *sh, t_cmd *cmd)
{
	char	*operand;
	char	*curpath;
	int		malloced;

	g_xt_stat = 0;
	malloced = 0;
	curpath = NULL;
	if (cmd->ac == 1)
	{
		operand = get_var(sh->env, "HOME");
		if (!operand || !operand[0])
		{
			g_xt_stat = 1;
			return (CMD_WAIT
				+ ft_err4(sh->exec_name, cmd->av[0], "HOME not set\n", NULL));
		}
	}
	else
		operand = cmd->av[1];
	if (operand[0] == '/')
		curpath = operand;
	else
	{
		if (!(operand[0] == '.'
				&& (operand[1] == '/' || !operand[1] || (operand[1] == '.'
						&& (operand[2] == '/' || !operand[2])))))
			curpath = search_path(get_var(sh->env, "CDPATH"), operand, 1);
		if (!curpath)
			curpath = ft_cat3(get_var(sh->env, "PWD"), "/", operand);
		if (!curpath)
			exit(EXIT_FAILURE);
		malloced = 1;
	}
	if (!make_canonical(curpath))
	{
		if (malloced)
			free(curpath);
		return (CMD_WAIT);
	}
	if (chdir(curpath))
	{
		ft_err4("minishell: cd", curpath, strerror(errno), NULL);
		g_xt_stat = 1;
	}
	else
	{
		printf("%s\n", curpath);
		export_single(sh, cmd,
			ft_cat3("OLDPWD=", get_var(sh->env, "PWD"), NULL));
		export_single(sh, cmd, ft_cat3("PWD=", curpath, NULL));
	}
	if (malloced)
		free(curpath);
	return (CMD_WAIT);
}
