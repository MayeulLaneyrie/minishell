/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newdel_cmd_sh.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:24:59 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/03/17 19:51:50 by mlaneyri         ###   ########.fr       */
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

	if (!*cmd)
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

t_sh	*new_sh(void)
{
	t_sh	*ret;

	ret = malloc(sizeof(t_sh));
	if (!ret)
		return (NULL);
	ret->cmd = NULL;
	ret->xt_stat = 0;
	return (ret);
}

void	*del_sh(t_sh **sh)
{
	if (!*sh)
		return (NULL);
	del_cmd(&(*sh)->cmd);
	free(*sh);
	*sh = NULL;
	return (NULL);
}
