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
			return (del_split(dirs, &ft_free));
		if (!access(temp, F_OK))
			return (temp + (unsigned long)del_split(dirs, &ft_free));
		free(temp);
	}
	del_split(dirs, &ft_free);
	return (NULL);
}

int	cmd_proc(t_sh *sh, t_cmd *cmd, int do_fork)
{
	if (!ft_strchr(cmd->av[0], '/'))
	{
		cmd->builtin_id = builtin_search(cmd->av[0]);
		if (cmd->builtin_id >= 0)
			return (builtin_exec(sh, cmd));
		cmd->path = search_path(get_var(sh->envp, "PATH"), cmd->av[0]);
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
	execve(cmd->path, cmd->av, sh->envp);
	excvefail_handler(cmd->path, sh);
	ft_free((void **)&(cmd->path));
	return (CMD_EXIT);
}

int	spawn_pipe_cmd(t_sh *sh, t_cmd *cmd)
{
	close(cmd->pipe_in[STDOUT]);
	close(cmd->pipe_out[STDIN]);
	cmd_proc(sh, cmd, 0);
	close(cmd->pipe_in[STDIN]);
	close(cmd->pipe_out[STDOUT]);
	exit(g_xt_stat);
}

int	pipeline_spawner(t_sh *sh)
{
	int		i;
	int		pid;
	t_cmd	**cmd;

	cmd = (t_cmd **)sh->pipeline->data;
	i = -1;
	while (++i < sh->pipeline->len)
	{
		if (i)
			cmd[i]->redirect[STDIN] = 1;
		if (i != sh->pipeline->len - 1)
		{
			cmd[i]->redirect[STDOUT] = 1;
			if (pipe(cmd[i]->pipe_out))
				exit(EXIT_FAILURE);
			cmd[i + 1]->pipe_in[STDIN] = cmd[i]->pipe_out[STDIN];
			cmd[i + 1]->pipe_in[STDOUT] = cmd[i]->pipe_out[STDOUT];
		}
		pid = fork();
		if (pid < 0)
			exit(EXIT_FAILURE);
		if (!pid)
			spawn_pipe_cmd(sh, cmd[i]);
		else if (i)
		{
			close(cmd[i]->pipe_in[STDIN]);
			close(cmd[i]->pipe_in[STDOUT]);
		}
	}
	return (0);
}

int	main_part2(t_sh *sh)
{
	int		stat;
	t_cmd	**cmd;

	printf("COUILLE\n");
	cmd = (t_cmd **)sh->pipeline->data;
	printf("%d\n", sh->pipeline->len);
	if (sh->pipeline->len != 1)
		stat = pipeline_spawner(sh);
	else
	{
		printf("BITE\n");
		stat = cmd_proc(sh, cmd[0], 1);
	}
	if (stat || cmd[sh->pipeline->len - 1]->pid < 0)
		return (stat == CMD_EXIT);
	waitpid(cmd[sh->pipeline->len - 1]->pid, &stat, 0);
	g_xt_stat = WEXITSTATUS(stat);
	return (0);
}
