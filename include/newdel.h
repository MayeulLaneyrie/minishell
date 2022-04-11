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

void	*del_cmd(t_cmd **cmd);

/*
**	t_sh (newdel_cmd_sh.c):
**	ret->envp = envp;
**	cmd = NULL
**	xt_stat = 0
*/

t_sh	*new_sh(int ac, char **av, char **envp);

void	*del_sh(t_sh **sh);

/*
**	new_av initialize the char **av in sh->cmd
**	av and av[0] are both malloced of 1 respectively char ** and char *.
*/

char	**new_av(t_cmd *cmd);

#endif
