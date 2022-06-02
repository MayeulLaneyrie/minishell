/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:21:39 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/06/02 17:21:40 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
**	Renvoie NULL si la variable n'a pas été trouvée.
**	env doit être correctement formatté.
*/
char	*get_var(t_split *env, char *name);

int		set_var(t_split *env, char *name, char *value);

int		get_var_index(t_split *env, char *name, int even_unset);

int		export_single(t_split *env, char *s);

int		check_identifier(char *s, int stop_at_eq);

#endif
