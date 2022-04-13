#include "../include/minishell.h"

int	cnf_handler(t_sh *sh, t_cmd *cmd)
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
	sh->xt_stat = 127;
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

char	*search_path(char *path, char *name)
{
	t_split	*dirs;
	char	*temp;
	int		i;

	dirs = ft_split(path, ':');
	if (!dirs)
		return (NULL);
	i = -1;
	while (dirs->data[++i])
	{
		temp = ft_cat3(dirs->data[i], "/", name);
		if (!temp)
			return (del_split(&dirs));
		if (!access(temp, F_OK))
			return (temp + (unsigned long)del_split(&dirs));
		free(temp);
	}
	del_split(&dirs);
	return (NULL);
}

int	cmd_proc(t_sh *sh, t_cmd *cmd)
{
	if (!ft_strchr(cmd->av[0], '/'))
	{
		cmd->builtin_id = builtin_search(cmd->av[0]);
		if (cmd->builtin_id >= 0)
			return (builtin_exec(sh, cmd));
		cmd->path = search_path(get_var(sh->envp, "PATH"), cmd->av[0]);
		if (!cmd->path)
			return (cnf_handler(sh, cmd) + CMD_NOWAIT);
	}
	else
	{
		cmd->path = ft_strdup(cmd->av[0]);
		if (!cmd->path)
			return (CMD_EXIT);
	}
	cmd->pid = fork();
	if (cmd->pid)
		return (CMD_WAIT);
	execve(cmd->path, cmd->av, sh->envp);
	excvefail_handler(cmd->path, sh);
	ft_free((void **)&(cmd->path));
	return (CMD_EXIT);
}

int	main_part2(t_sh *sh)
{
	int	stat;

	stat = cmd_proc(sh, sh->cmd);
	if (stat || sh->cmd->pid < 0)
		return (stat != CMD_EXIT);
	waitpid(sh->cmd->pid, &stat, 0);
	sh->xt_stat = WEXITSTATUS(stat);
	return (0);
}
