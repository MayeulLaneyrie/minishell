#include "../include/minishell.h"

int	bi_cd(t_sh *sh, t_cmd *cmd)
{
	char	*operand;
	char	*curpath;
	int		malloced;
	int		display;
	char	*temp;

	g_xt_stat = 0;
	malloced = 0;
	display = 0;
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
	else if (cmd->av[1][0] == '-' && !cmd->av[1][1])
	{
		operand = get_var(sh->env, "OLDPWD");
		display = 1;
		if (!operand)
		{
			g_xt_stat = 1;
			write(2, "minishell: cd: OLDPWD not set\n", 30);
			return (CMD_NOWAIT);
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
		if (curpath)
			display = (curpath[0] == '/');
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
		if (display)
			printf("%s\n", curpath);
		/*
		**	TODO : implement set_var() to cleanup the mess that follows :
		*/
		temp = ft_cat3("OLDPWD=", get_var(sh->env, "PWD"), NULL);
		if (!temp)
			exit(EXIT_FAILURE);
		export_single(sh, cmd, temp);
		free(temp);
		temp = ft_cat3("PWD=", curpath, NULL);
		if (!temp)
			exit(EXIT_FAILURE);
		export_single(sh, cmd, temp);
		free(temp);
	}
	if (malloced)
		free(curpath);
	return (CMD_WAIT);
}
