/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:39:41 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/03/16 16:09:36 by mlaneyri         ###   ########.fr       */
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
**	constdest.h holds the prototypes of the constructor and destructor functions
*/
# include "./consdest.h"

typedef struct s_cmd
{
	int		ac;
	char	**av;
}	t_cmd;

/*
**	xt_status : The exit status of the last executed job. xt_stat should be the
**	return value of main().
*/
typedef struct s_sh
{
	t_cmd	*cmd;
	int		xt_stat;
}	t_sh;

#endif
