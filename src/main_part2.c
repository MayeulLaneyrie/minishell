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
			return (NULL);
		if (!access(temp, F_OK))
			return (temp + (unsigned long)del_split(&dirs));
		free(temp);
	}
	del_split(&dirs);
	return (NULL);
}

int	cmd_proc(t_sh *sh, t_cmd *cmd)
{
	char	*cmd_path;

	cmd_path = cmd->av[0];
	if (!ft_strchr(cmd_path, '/'))
	{
		cmd->builtin_id = builtin_search(cmd_path);
		if (cmd->builtin_id >= 0)
			return (builtin_exec(sh, cmd));
		cmd_path = search_path(get_var(sh->envp, "PATH"), cmd_path);
		if (!cmd_path)
			return (cnf_handler(sh, cmd) + 1);
	}
	cmd->pid = fork();
	if (cmd->pid)
		return (0);
	execve(cmd_path, cmd->av, sh->envp);
	return (1);
}

int	main_part2(t_sh *sh)
{
	int	stat;

	stat = cmd_proc(sh, sh->cmd);
	if (stat)
		return (stat < 0);
	if (sh->cmd->pid < 0)
		return (-1);
	waitpid(sh->cmd->pid, &stat, 0);
	del_cmd(&sh->cmd);
	sh->xt_stat = WEXITSTATUS(stat);
	return (0);
}
