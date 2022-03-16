/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newdel.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:18:20 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/03/16 16:24:45 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NEWDEL_H
# define NEWDEL_H

/*
**	t_cmd (newdel_cmd_sh.c):
*/

t_cmd	*new_cmd();

void	*del_cmd(t_cmd **cmd);

/*
**	t_sh (newdel_cmd_sh.c):
*/

t_sh	*new_sh();

void	*del_sh(t_sh **sh);

#endif
