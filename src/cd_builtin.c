#include "../include/minishell.h"

char	*set_operand(t_sh *sh, t_cmd *cmd, int *display)
{
	char	*operand;

	*display = 0;
	if (cmd->ac == 1)
	{
		operand = get_var(sh->env, "HOME");
		if (!operand || !operand[0])
		{
			ft_err4(sh->exec_name, cmd->av[0], "HOME not set\n", NULL);
			return (NULL);
		}
	}
	else if (cmd->av[1][0] == '-' && !cmd->av[1][1])
	{
		operand = get_var(sh->env, "OLDPWD");
		*display = 1;
		if (!operand)
		{
			write(2, "minishell: cd: OLDPWD not set\n", 30);
			return (NULL);
		}
	}
	else
		operand = cmd->av[1];
	return (operand);
}

char	*set_curpath(t_split *env, char *operand, int *display, int *mallocced)
{
	char	*curpath;

	mallocced = 0;
	curpath = NULL;
	if (operand[0] == '/')
		curpath = operand;
	else
	{
		if (!(operand[0] == '.'
				&& (operand[1] == '/' || !operand[1] || (operand[1] == '.'
						&& (operand[2] == '/' || !operand[2])))))
			curpath = search_path(get_var(env, "CDPATH"), operand, 1);
		if (curpath)
			*display = (curpath[0] == '/');
		if (!curpath)
			curpath = ft_cat3(get_var(env, "PWD"), "/", operand);
		*mallocced = 1;
	}
	return (curpath);
}

int	set_pwd(t_split *env, char *dir)
{
	set_var(env, "OLDPWD", get_var(env, "PWD"));
	set_var(env, "PWD", dir);
	return (0);
}

int	bi_cd(t_sh *sh, t_cmd *cmd)
{
	char	*dir;
	int		mallocced;
	int		display;
	int		n;


	dir = set_operand(sh, cmd, &display);
	g_xt_stat = (dir != NULL);
	if (!dir)
		return (CMD_NOWAIT);
	dir = set_curpath(sh->env, dir, &display, &mallocced);
	if (!dir)
		exit(EXIT_FAILURE);
	if (make_canonical(dir))
	{
		n = chdir(dir);
		if (n)
			g_xt_stat = 1 + ft_err4("minishell: cd", dir, strerror(errno), 0);
		if (!n && display)
			printf("%s\n", dir);
		if (!n && set_pwd(sh->env, dir))
			exit(EXIT_FAILURE);
	}
	if (mallocced)
		free(dir);
	return (CMD_NOWAIT);
}
