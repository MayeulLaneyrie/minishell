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

#endif
