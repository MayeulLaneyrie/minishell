/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newdel.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:18:20 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/03/17 19:52:30 by mlaneyri         ###   ########.fr       */
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
**	cmd = NULL
**	xt_stat = 0
*/

t_sh	*new_sh(void);

void	*del_sh(t_sh **sh);

#endif
