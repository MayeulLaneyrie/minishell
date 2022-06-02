/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newdel_cmd_sh.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:49:00 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/06/02 16:49:01 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**new_av(t_cmd *cmd)
{
	cmd->av = (char **)malloc(sizeof(char *) * 1);
	if (!cmd->av)
		return (NULL);
	cmd->av[0] = (char *)malloc(sizeof(char) * 1);
	if (!cmd->av[0])
		return (NULL);
	cmd->av[0][0] = '\0';
	return (cmd->av);
}

t_cmd	*new_cmd(void)
{
	t_cmd	*ret;

	ret = malloc(sizeof(t_cmd));
	if (!ret)
		return (NULL);
	ret->pid = 0;
	ret->builtin_id = -1;
	ret->path = NULL;
	ret->ac = 0;
	ret->av = NULL;
	ret->is_piped[STDIN] = 0;
	ret->is_piped[STDOUT] = 0;
	ret->red = NULL;
	return (ret);
}

void	*del_cmd(void *ptr)
{
	t_cmd	*cmd;
	int		i;

	cmd = (t_cmd *)ptr;
	if (!cmd)
		return (NULL);
	if (cmd->path != cmd->av[0])
		ft_free(cmd->path);
	if (cmd->av)
	{
		i = -1;
		while (++i < cmd->ac)
			ft_free((void *)cmd->av[i]);
		ft_free((void *)cmd->av);
	}
	ft_free((void *)cmd);
	return (NULL);
}

int	new_sh(int ac, char **av, char **envp, t_sh *sh)
{
	char	*tmp;

	(void)ac;
	if (!envp)
		return (-1);
	sh->env = load_env(envp);
	if (!sh->env)
		return (-1);
	tmp = get_pwd();
	if (!tmp)
		exit(EXIT_FAILURE);
	set_var(sh->env, "PWD", tmp);
	free(tmp);
	sh->exec_name = av[0];
	sh->pipeline = NULL;
	return (0);
}

void	*del_sh(t_sh *sh)
{
	if (!sh)
		return (NULL);
	del_split(sh->pipeline, &del_cmd);
	del_split(sh->env, &ft_free);
	return (NULL);
}
