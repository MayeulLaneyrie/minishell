/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrah <bifrah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:39:41 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/03/31 19:07:13 by bifrah           ###   ########.fr       */
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

# include <stdbool.h>

# include "../libft/libft.h"

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

/*
**	newdel.h holds the prototypes of all constructor and destructor functions.
**	Don't hesitate to put inside of it all the constructors and destructors of
**	your own structures. All update to a structure definition should result in
**	an update of its constructor and destructor.
*/

# include "./newdel.h"

/*
**	First steps of shell operations : reading a line, lexing and parsing it.
**	Should return 0 if a command line has been correctly parsed, and any other
**	value to indicate that minishell should exit.
**	When called, cmd member of sh won't have been initialized yet.
**	When returning, cmd should be correctly initialized, unless exiting shell
**	is required.
*/

int	main_part1(t_sh *sh);

int	count_quote(char *rdline);
int	find_quote(char *rdline);
int	ac_of_av(char **av);

int	main_part2(t_sh *sh);

# define NULL_RDLINE	1
# define WRONG_NB_QUOTE	2
# define BLANK_RDLINE	3

#endif
