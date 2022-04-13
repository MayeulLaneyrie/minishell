/*
**	newdel.h contient les prototypes de tous les constructeurs et destructeurs.
**	Ne pas hésiter a y rajouter les constructeurs et destructeurs de ses propres
**	structures. Chaque modification apportée a la définition d'une structure
**	devra donner lieu a une mise a jour de son constructeur et destructeur.
*/

#ifndef NEWDEL_H
# define NEWDEL_H

/*
**	t_cmd (newdel_cmd_sh.c):
**	ac = 0
**	av = NULL
*/

t_cmd	*new_cmd(void);

void	*del_cmd(void *cmd);

/*
**	t_sh (newdel_cmd_sh.c):
**	ret->envp = envp;
**	cmd = NULL
**	xt_stat = 0
*/

int		new_sh(int ac, char **av, char **envp, t_sh *sh);

void	*del_sh(t_sh *sh);

#endif
