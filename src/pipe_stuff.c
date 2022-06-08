/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 16:18:19 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/06/08 04:28:57 by lnr              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	spawn_pipe_cmd(t_sh *sh, t_cmd *cmd)
{
	sig_init(SIGINT, SIG_DFL);
	sig_init(SIGQUIT, SIG_DFL);
	if (cmd->is_piped[STDIN])
	{
		close(cmd->pipe_in[STDOUT]);
		dup2(cmd->pipe_in[STDIN], STDIN);
		close(cmd->pipe_in[STDIN]);
	}
	if (cmd->is_piped[STDOUT])
	{
		close(cmd->pipe_out[STDIN]);
		dup2(cmd->pipe_out[STDOUT], STDOUT);
		close(cmd->pipe_out[STDOUT]);
	}
	cmd_proc(sh, cmd, 0);
	if (cmd->is_piped[STDIN])
		close(cmd->pipe_in[STDIN]);
	if (cmd->is_piped[STDOUT])
		close(cmd->pipe_out[STDOUT]);
	return (CMD_EXIT);
}

int	pipe_gen(t_cmd **cmd, int i)
{
	cmd[i]->is_piped[STDOUT] = 1;
	if (pipe(cmd[i]->pipe_out))
		return (ft_err4("minishell: pipe failed\n", NULL, NULL, NULL) - 1);
	cmd[i + 1]->pipe_in[STDIN] = cmd[i]->pipe_out[STDIN];
	cmd[i + 1]->pipe_in[STDOUT] = cmd[i]->pipe_out[STDOUT];
	return (0);
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
			if (pipe_gen(cmd, i))
				return (CMD_NOWAIT);
		cmd[i]->pid = fork();
		if (cmd[i]->pid < 0)
			exit(EXIT_FAILURE);
		if (!cmd[i]->pid)
			return (spawn_pipe_cmd(sh, cmd[i]));
		else if (i)
		{
			close(cmd[i]->pipe_in[STDIN]);
			close(cmd[i]->pipe_in[STDOUT]);
		}
	}
	return (CMD_WAIT);
}
