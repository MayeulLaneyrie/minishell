#include "../include/minishell.h"

int	exit_arg_checker(char *s)
{
	while (ft_strchr("\t \n", *s) && *s)
		s++;
	if (*s == '+' || *s == '-')
		s++;
	if (!ft_isdigit(*s))
		return (-1);
	while (ft_isdigit(*s))
		s++;
	while (ft_strchr("\t \n", *s) && *s)
		s++;
	return (*s);
}

int	bi_exit(t_sh *sh, t_cmd *cmd)
{
	write(2, "exit\n", 5);
	if (cmd->ac < 2)
		return (-1);
	if (exit_arg_checker(cmd->av[1]))
	{
		sh->xt_stat = 2;
		return (ft_err4(sh->exec_name, cmd->av[0], cmd->av[1],
				"numeric argument required\n") - 1);
	}
	if (cmd->ac > 2)
	{
		sh->xt_stat = 1;
		return (ft_err4(sh->exec_name, cmd->av[0], "too many arguments\n", NULL)
			+ 1);
	}
	sh->xt_stat = ft_atoi(cmd->av[1]);
	return (-1);
}

int	builtin_search(char *s)
{
	static const char	*builtins[8] = {"echou", "cd", "pwd", "export", "unset",
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
