#include "../include/minishell.h"

int	bi_exit(t_sh *sh, t_cmd *cmd)
{
	(void)sh;
	(void)cmd;
	if (cmd->ac < 2)
		return (-1);
	sh->xt_stat = ft_atoi(cmd->av[1]);
	return (-1);
}

int	builtin_search(char *s)
{
	static const char	*builtins[8] = {"echo", "cd", "pwd", "export", "unset",
		"env", "exit", NULL};
	int					i;

	i = -1;
	while (builtins[++i])
		if (!ft_strncmp(builtins[i], s, 7))
			return (i);
	return (-1);
}

int	builtin_exec(t_sh *sh, t_cmd *cmd)
{
	static const t_bi	builtins[8] = {NULL, NULL, NULL, NULL, NULL, NULL,
		&bi_exit, NULL};
	if (cmd->builtin_id != 6)
	{
		printf("%s not implemented as of Mark 1\n", cmd->av[0]);
		sh->xt_stat = 127;
		return (-1);
	}
	return (builtins[cmd->builtin_id](sh, cmd));
}
