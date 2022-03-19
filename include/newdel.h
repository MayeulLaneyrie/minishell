/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newdel.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrah <bifrah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:18:20 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/03/19 17:17:15 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	newdel.h holds the prototypes of all constructor and destructor functions.
**	Don't hesitate to put inside of it all the constructors and destructors of
**	your own structures. All update to a structure definition should result in
**	an update of its constructor and destructor.
*/

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

/*
**	void ** (newdel_cmd_sh.c):
**	ONLY IF SPLIT IS NULL TERMINATED del_split may be called passing a negative
**	size. It will be ignored and all memory pointed by the pointers in split
**	will be freed until a null pointer is reached.
*/

int		del_split(void ***split, int size);

#endif
