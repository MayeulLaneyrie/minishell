/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 01:38:14 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/03/23 16:18:54 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	structures.h is the dedicated place to define custom structures, expecially
**	if they are going to be refered to in other header files.
*/

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_cmd
{
	int		ac;
	char	**av;
}	t_cmd;

/*
**	cmd : a parsed simple command
**	xt_stat : The exit status of the last executed job. xt_stat should be the
**	return value of main().
*/
typedef struct s_sh
{
	char	**envp;
	t_cmd	*cmd;
	int		xt_stat;
}	t_sh;

typedef struct s_split
{
	void	**data;
	int		len;
	int		size;
}	t_split;

#endif
