/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_central.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrah <bifrah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:47:01 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/06/03 16:27:33 by bifrah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (!(cmd->is_piped[STDIN] + cmd->is_piped[STDOUT]))
		write(2, "exit\n", 5);
	if (cmd->ac < 2)
		return (CMD_EXIT);
	if (exit_arg_checker(cmd->av[1]))
	{
		g_xt_stat = 2;
		return (ft_err4(sh->exec_name, cmd->av[0], cmd->av[1],
				"numeric argument required\n") + CMD_EXIT);
	}
	if (cmd->ac > 2)
	{
		g_xt_stat = 1;
		return (ft_err4(sh->exec_name, cmd->av[0], "too many arguments\n", NULL)
			+ CMD_NOWAIT);
	}
	g_xt_stat = ft_atoi(cmd->av[1]);
	return (CMD_EXIT);
}

int	builtin_search(char *s)
{
	static const char	*builtins[8] = {"echo", "cd", "pwd", "export",
		"unset", "env", "exit", NULL};
	int					i;

	i = -1;
	while (builtins[++i])
		if (!ft_strncmp(builtins[i], s, 7))
			return (i);
	return (-1);
}

int	builtin_exec(t_sh *sh, t_cmd *cmd)
{
	static const t_bi	builtins[8] = {&bi_echo, &bi_cd, &bi_pwd, &bi_export,
		&bi_unset, &bi_env, &bi_exit, NULL};
	int					ret;
	int					save_fd[3];
	int					i;

	i = -1;
	g_xt_stat = 1;
	while (++i < 3)
		save_fd[i] = dup(i);
	if (apply_redir(cmd))
		return (CMD_NOWAIT);
	g_xt_stat = 0;
	ret = builtins[cmd->builtin_id](sh, cmd);
	i = -1;
	while (++i < 3)
	{
		dup2(save_fd[i], i);
		close(save_fd[i]);
	}
	return (ret);
}