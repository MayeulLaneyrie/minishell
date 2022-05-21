#include "../include/minishell.h"

int	bi_env(t_sh *sh, t_cmd *cmd)
{
	int	i;

	(void)cmd;
	i = -1;
	while (++i < sh->env->len)
		printf("%s\n", ((char **)sh->env->data)[i]);
	return (CMD_NOWAIT);
}

int	check_identifier(char *s, t_sh *sh, t_cmd *cmd, int stop_at_eq)
{
	int	i;
	int	failed;

	failed = 0;
	if (!(ft_isalpha(*s) || *s == '_'))
		failed -= 1;
	i = 0;
	while (s[++i] != '=' && s[i])
		if (!(ft_isalnum(s[i]) || s[i] == '_'))
			failed -= 2;
	if (s[i] == '=' && !stop_at_eq)
		failed -= 3;
	if (failed)
		ft_err4(sh->exec_name, cmd->av[0], s, "not a valid identifier\n");
	return (failed);
}

int	export_single(t_sh *sh, t_cmd *cmd, char *s)
{
	int		n;
	char	*cpy;

	if (check_identifier(s, sh, cmd, 1))
		return (-1);
	n = get_var_index(sh->env, s);
	if (n >= 0 && !ft_strchr(s, '='))
		return (0);
	cpy = ft_strdup(s);
	if (!cpy)
		exit(EXIT_FAILURE);
	if (n < 0)
		return (3 * split_push(sh->env, cpy, sh->env->len));
	free(((void **)sh->env->data)[n]);
	return (3 * split_push(sh->env, cpy, n));
}

int	bi_export(t_sh *sh, t_cmd *cmd)
{
	int	i;
	int	xt;
	int	n;

	if (cmd->ac == 1)
	{
		i = -1;
		while (++i < sh->env->len)
			printf("%s\n", ((char **)sh->env->data)[i]);
		return (CMD_NOWAIT);
	}
	i = 0;
	xt = 0;
	while (++i < cmd->ac)
	{
		n = export_single(sh, cmd, cmd->av[i]);
		if (n < -2)
			exit(EXIT_FAILURE);
		xt += n;
	}
	g_xt_stat = xt != 0;
	return (CMD_NOWAIT);
}

int	bi_unset(t_sh *sh, t_cmd *cmd)
{
	int	i;
	int	n;

	g_xt_stat = 0;
	i = 0;
	while (++i < cmd->ac)
	{
		if (!check_identifier(cmd->av[i], sh, cmd, 0))
		{
			n = get_var_index(sh->env, cmd->av[i]);
			if (n >= 0)
			{
				free(((void **)sh->env->data)[n]);
				while (++n < sh->env->len)
					((char **)sh->env->data)[n - 1]
						= ((char **)sh->env->data)[n];
				sh->env->len--;
			}
		}
		else
			g_xt_stat = 1;
	}
	return (CMD_NOWAIT);
}
