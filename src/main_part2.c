#include "../include/minishell.h"

int	cnf_handler(t_cmd *cmd)
{
	char	*s;
	int		l;

	l = ft_strlen(cmd->av[0]) + 21;
	s = malloc(l + 1);
	if (!s)
		return (-1);
	s[0] = 0;
	ft_strlcat(s, cmd->av[0], l);
	ft_strlcat(s, ": command not found\n", l);
	write(2, s, l);
	free(s);
	g_xt_stat = 127;
	return (0);
}

int	excvefail_handler(char *path, t_sh *sh)
{
	char	*prefix;

	prefix = ft_cat3(sh->exec_name, ": ", path);
	if (!prefix)
		return (0);
	perror(prefix);
	free(prefix);
	return (0);
}

int	cmd_proc(t_sh *sh, t_cmd *cmd, int do_fork)
{
	if (!ft_strchr(cmd->av[0], '/'))
	{
		cmd->builtin_id = builtin_search(cmd->av[0]);
		if (cmd->builtin_id >= 0)
			return (builtin_exec(sh, cmd));
		cmd->path = search_path(get_var(sh->env, "PATH"), cmd->av[0], 0);
		if (!cmd->path)
			return (cnf_handler(cmd) + CMD_NOWAIT);
	}
	else
	{
		cmd->path = ft_strdup(cmd->av[0]);
		if (!cmd->path)
			return (CMD_EXIT);
	}
	if (do_fork)
	{
		cmd->pid = fork();
		if (cmd->pid)
			return (CMD_WAIT);
	}
	execve(cmd->path, cmd->av, (char **)sh->env->data);
	excvefail_handler(cmd->path, sh);
	return (CMD_EXIT);
}

int	main_part2(t_sh *sh)
{
	int		stat;
	t_cmd	**cmd;
	int		i;

	cmd = (t_cmd **)sh->pipeline->data;
	if (sh->pipeline->len != 1)
		stat = pipeline_spawner(sh);
	else
		stat = cmd_proc(sh, cmd[0], 1);
	if (stat || cmd[sh->pipeline->len - 1]->pid < 0)
		return (stat == CMD_EXIT);
	i = -1;
	while (++i < sh->pipeline->len)
		waitpid(cmd[i]->pid, &stat, 0);
	g_xt_stat = WEXITSTATUS(stat);
	return (0);
}
