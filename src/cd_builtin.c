#include "../include/minishell.h"

int	bi_cd(t_sh *sh, t_cmd *cmd)
{
	char	*curpath;

	g_xt_stat = 0;
	if (cmd->ac == 1 && !get_var((char **)sh->env->data, "HOME"))
	{
		g_xt_stat = 1;
		return (CMD_WAIT
			+ ft_err4(sh->exec_name, cmd->av[0], "HOME not set\n", NULL));
	}

	return (CMD_WAIT);
}
