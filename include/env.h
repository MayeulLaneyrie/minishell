#ifndef ENV_H
# define ENV_H

/*
**	Copie les données d'envp dans un t_split. Permet d'altérer l'environnement.
*/
t_split	*load_env(char **envp);

/*
**	Celle-ci est assez explicite. Important de noter que les données renvoyées
**	ne sont pas copiées, ce qui signifie qu'on n'a pas à les free(), mais aussi
**	qu'on pourrait vouloir les copier soi-même pour un usage sur le long terme,
**	car des appels ultérieurs à set_var() et unset_var() pourraient modifier les
**	données pointées.
*/
char	*get_var(t_split *env, char *name);

#endif
