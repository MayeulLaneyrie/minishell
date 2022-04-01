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
