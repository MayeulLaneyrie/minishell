#ifndef SPLIT_UTILS_H
# define SPLIT_UTILS_H

/*
**	Dans split_utils.c
*/

/*
**	new_split alloue à data un tableau de void* de taille n.
**	len est initialisé à 0, car le split est encore vide de données.
*/

t_split	*new_split(int n);

void	*del_split(t_split **split);

/*
**	list_to_split() et split_to_list() convertissent respectivement un t_list
**	en t_split et inversement. Toutes les ressources de la structure d'origine
**	sont libérées, à part les données qu'elle contenait, qui sont transférées.
*/

t_split	*list_to_split(t_list **lst);

t_list	*split_to_list(t_split **split);

#endif
