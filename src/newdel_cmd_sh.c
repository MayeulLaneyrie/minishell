/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newdel_cmd_sh.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrah <bifrah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:24:59 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/03/23 01:39:19 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*ret;

	ret = malloc(sizeof(t_cmd));
	if (!ret)
		return (NULL);
	ret->ac = 0;
	ret->av = NULL;
	return (ret);
}

void	*del_cmd(t_cmd **cmd)
{
	int	i;

	if (!cmd || !*cmd)
		return (NULL);
	if ((*cmd)->av)
	{
		i = -1;
		while (++i < (*cmd)->ac)
			free((*cmd)->av[i]);
		free((*cmd)->av);
	}
	free(*cmd);
	*cmd = NULL;
	return (NULL);
}

t_sh	*new_sh(char **envp)
{
	t_sh	*ret;

	if (!envp)
		return (NULL);
	ret = malloc(sizeof(t_sh));
	if (!ret)
		return (NULL);
	ret->envp = envp;
	ret->cmd = NULL;
	ret->xt_stat = 0;
	return (ret);
}

void	*del_sh(t_sh **sh)
{
	if (!sh || !*sh)
		return (NULL);
	del_cmd(&(*sh)->cmd);
	free(*sh);
	*sh = NULL;
	return (NULL);
}
