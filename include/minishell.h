#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <stdbool.h>

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include <string.h>

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>

# include <dirent.h>

# include <signal.h>

/*
**	Just a regular libft, with doubly chained lists.
*/
# include "../libft/libft.h"

/*
**	structures.h is the dedicated place to define custom structures, expecially
**	if they are going to be refered to in other header files.
*/
# include "./structures.h"

/*
**	newdel.h holds the prototypes of all constructor and destructor functions.
**	Don't hesitate to put inside of it all the constructors and destructors of
**	your own structures. All update to a structure definition should result in
**	an update of its constructor and destructor.
*/
# include "./newdel.h"

/*
**	env.h holds the definition of environment manipulation functions.
*/
# include "./env.h"

/*
**	First steps of shell operations : reading a line, lexing and parsing it.
**	Should return 0 if a command line has been correctly parsed, and any other
**	value to indicate that minishell should exit.
**	When called, cmd member of sh won't have been initialized yet.
**	When returning, cmd should be correctly initialized, unless exiting shell
**	is required.
*/

int		main_part1(t_sh *sh);

int		fill_cmd(t_sh *sh, char *rdline);
int		word_cpy(t_sh *sh, int j, char *str, int i);
int		word_len(char *str, int i);
bool	is_meta(char c);

int		count_quote(char *rdline);
int		find_quote(char *rdline);
int		ac_of_av(char **av);
char	**ft_split_b(char const *s, char c);

int		main_part2(t_sh *sh);

# define NULL_RDLINE	1
# define WRONG_NB_QUOTE	2
# define BLANK_RDLINE	3

#endif
