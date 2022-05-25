#include "../include/minishell.h"

int	spawn_pipe_cmd(t_sh *sh, t_cmd *cmd)
{
	if (cmd->is_piped[STDIN])
	{
		close(cmd->pipe_in[STDOUT]);
		dup2(cmd->pipe_in[STDIN], STDIN);
	}
	if (cmd->is_piped[STDOUT])
	{
		close(cmd->pipe_out[STDIN]);
		dup2(cmd->pipe_out[STDOUT], STDOUT);
	}
	cmd_proc(sh, cmd, 0);
	if (cmd->is_piped[STDIN])
		close(cmd->pipe_in[STDIN]);
	if (cmd->is_piped[STDOUT])
		close(cmd->pipe_out[STDOUT]);
	exit(g_xt_stat);
}

int	pipeline_spawner(t_sh *sh)
{
	int		i;
	t_cmd	**cmd;

	cmd = (t_cmd **)sh->pipeline->data;
	i = -1;
	while (++i < sh->pipeline->len)
	{
		if (i)
			cmd[i]->is_piped[STDIN] = 1;
		if (i != sh->pipeline->len - 1)
		{
			cmd[i]->is_piped[STDOUT] = 1;
			if (pipe(cmd[i]->pipe_out))
				exit(EXIT_FAILURE);
			cmd[i + 1]->pipe_in[STDIN] = cmd[i]->pipe_out[STDIN];
			cmd[i + 1]->pipe_in[STDOUT] = cmd[i]->pipe_out[STDOUT];
		}
		cmd[i]->pid = fork();
		if (cmd[i]->pid < 0)
			exit(EXIT_FAILURE);
		if (!cmd[i]->pid)
			spawn_pipe_cmd(sh, cmd[i]);
		else if (i)
		{
			close(cmd[i]->pipe_in[STDIN]);
			close(cmd[i]->pipe_in[STDOUT]);
		}
	}
	return (0);
}
