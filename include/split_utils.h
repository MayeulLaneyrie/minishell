/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:21:17 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/06/02 17:21:31 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPLIT_UTILS_H
# define SPLIT_UTILS_H

# include <stdlib.h>
# include "../include/structures.h"
# include "../libft/libft.h"

/*
**	Dans split_utils.c
*/

/*
**	new_split alloue à data un tableau de void* de taille n.
**	len est initialisé à 0, car le split est encore vide de données.
*/

t_split	*new_split(int n);

void	*del_split(t_split *split, void *(*del)(void *));

/*
**	list_to_split() et split_to_list() convertissent respectivement un t_list
**	en t_split et inversement. Toutes les ressources de la structure d'origine
**	sont libérées, à part les données qu'elle contenait, qui sont transférées.
*/

t_split	*list_to_split(t_list **lst);

t_list	*split_to_list(t_split **split);

int		split_extend(t_split *split, int n);

int		split_push(t_split *split, void *data, int index);

#endif
