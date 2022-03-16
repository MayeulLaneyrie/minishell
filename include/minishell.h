/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:39:41 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/03/16 16:23:47 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# include <string.h>

# include <readline/readline.h>
# include <readline/history.h>

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>

# include <dirent.h>

# include <signal.h>

# include "../libft/libft.h"

/*
**	newdel.h holds the prototypes of all constructor and destructor functions.
**	Don't hesitate to put inside of it all the constructors and destructors of
**	your own structures. All update to a structure definition should result in
**	an update of its constructor and destructor.
*/
# include "./consdest.h"

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
	t_cmd	*cmd;
	int		xt_stat;
}	t_sh;

#endif
