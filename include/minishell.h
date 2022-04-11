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
**	Juste une libft normale, avec des chaînes doublement chainées.
*/
# include "../libft/libft.h"

/*
**	structures.h est le lieu dedié pour définir des structures custom,
**	en particulier si d'autres fichiers .h y font référence
*/
# include "./structures.h"

/*
**	newdel.h contient les prototypes de tous les constructeurs et destructeurs.
**	Ne pas hésiter a y rajouter les constructeurs et destructeurs de ses propres
**	structures. Chaque modification apportée a la définition d'une structure
**	devra donner lieu a une mise a jour de son constructeur et destructeur.
*/
# include "./newdel.h"

/*
**	env.h contient la définition de fonctions de gestion de l'environnement.
*/
# include "./env.h"

/*
**	Premières étapes du fonctionnement du shell :  lire une ligne, la découper
**	et la parser. Doit renvoyer 0 si une ligne de commande a été correctement
**	parsée, et n'importe quelle autre valeur pour indiquer que minishell doit
**	s'arrêter.
**	A l'appel, sh->cmd n'aura pas encore été initialisé. Au retour, cmd devra
**	avoir été correctement initialisé, a moins qu'il faille quitter le shell.
*/

int		main_part1(t_sh *sh);

int		fill_cmd(t_sh *sh, t_rl *rl);
char	*word_cpy(t_sh *sh, t_rl *rl, int i);
int		word_len(t_rl *rl, int i);
void	clean_d_quote(t_sh *sh);

/*
**	util1_part1.c
*/
int		count_quote(char *rdline);
bool	find_d_quote(char *rdline);
bool	find_quote(char *rdline);
bool	is_meta(char c);
bool	is_space(char c);

/*
**	util2_part1.c
*/
int		ac_of_av(char **av);
char	**create_tmp(char **av);
bool	realloc_tab(t_sh *sh, t_rl *rl, int i);

/*
**	ft_split_b.c
*/
char	**ft_split_b(char const *s, char c);
char	**free_split_b(char **array);

/*
**	Étapes suivantes du fonctionnement du shell : fork(), recherche d'une
**	builtin ou du chemin du binaire à exécuter, execve() dans le process fils
**	et waitpid() dans le process père.
*/

int		main_part2(t_sh *sh);

/*
**	Valeur de retour de cmd_proc() :
**		- !=0 : Process fils sans execve (command not found, execve fail ou
**			builtin). Ne pas attendre de process fils et return directement,
			le shell doit exit. L'exit_status aura été fixé à l'erreur.
**		- 0 : Process père, attendre le statut d'exit.
*/
int		cmd_proc(t_sh *sh, t_cmd *cmd);

/*
**	Dans builtin_central.c :
*/

int		builtin_search(char *s);
int		builtin_exec(t_sh *sh, t_cmd *cmd);

# define MALLOC_ERROR	1
# define WRONG_NB_QUOTE	2
# define NULL_RDLINE	3
# define BLANK_RDLINE	4

#endif
