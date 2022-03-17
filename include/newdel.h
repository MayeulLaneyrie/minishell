/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newdel.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrah <bifrah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:18:20 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/03/17 22:46:55 by bifrah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NEWDEL_H
# define NEWDEL_H

/*
**	t_cmd (newdel_cmd_sh.c):
**	ac = 0
**	av = NULL
*/

t_cmd	*new_cmd(void);

void	*del_cmd(t_cmd **cmd);

/*
**	t_sh (newdel_cmd_sh.c):
**	ret->envp = envp;
**	cmd = NULL
**	xt_stat = 0
*/

t_sh	*new_sh(char **envp);

void	*del_sh(t_sh **sh);

#endif
