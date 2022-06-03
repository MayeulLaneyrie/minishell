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

# define METACHAR "\t\n|< >"
# define SPACES "\t\n\r\v\f "

# define GNL_BUFFER_SIZE 256

/*
**	Valeur de retour de cmd_proc() :
**		- <0 : Le shell doit exit (exit, erreur fatale ou execve fail)
**		- 0 : Process père, attendre le statut d'exit.
**		- >0 : Pas d'exit, mais pas de process fils à attendre (builtin).
*/
# define CMD_EXIT -1
# define CMD_WAIT 0
# define CMD_NOWAIT 1

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define RED_IN 1
# define RED_OUT 2

# define RED_TRUNC 1
# define RED_APPEND 2

# define MALLOC_ERROR 1
# define WRONG_NB_QUOTE 2
# define NULL_RDLINE 3
# define BLANK_RDLINE 4

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
**	builtins.h contient les définitions des builtins.
*/
# include "./builtins.h"

/*
**	env.h contient la définition de fonctions de gestion de l'environnement.
*/
# include "./env.h"

extern int	g_xt_stat;

/*
**	Premières étapes du fonctionnement du shell :  lire une ligne, la découper
**	et la parser. Doit renvoyer 0 si une ligne de commande a été correctement
**	parsée, et n'importe quelle autre valeur pour indiquer que minishell doit
**	s'arrêter.
**	A l'appel, sh->cmd n'aura pas encore été initialisé. Au retour, cmd devra
**	avoir été correctement initialisé, a moins qu'il faille quitter le shell.
*/
int		main_part1(t_sh *sh);
int		parse_cmd(char *s, t_sh *sh);
int		word_len(char *s);
int		word_cpy(char *dst, char *src);
t_split	*cut_words(char *s, t_cmd *cmd);

/*
**	Dans dollar_subst.c :
*/

char	*all_dollar_subst(t_split *env, char *s);

/*
**	Dans gnl.c, juste un gnl :
*/
int		get_next_line(char **line);

/*
**	Dans quote_split.c : (Un split qui suit les règles de quoting)
*/
t_split	*quote_split(char *s, char *set);

/*
**	Dans utils.c :
*/
int		check_quote(char *s);
int		check_pipe(char *s);
int		check_redir(char *s);
int		check_redirect(char *s, t_cmd *cmd, t_list *lst);

/*
**	Dans var_env.c :
*/
int		check_env_var(char *s);
int		convert_env_vars(t_sh *sh, char **s);

/*
**	Dans cmd_launcher.c : (Lancement d'une commande)
*/
int		main_part2(t_sh *sh);
int		cmd_proc(t_sh *sh, t_cmd *cmd, int do_fork);

/*
**	Dans pipe_stuff.c : (Prépare l'exécution d'un pipeline)
*/
int		pipeline_spawner(t_sh *sh);

/*
**	Dans pwd_builtin.c : (Renvoie le pwd, doit etre free) :
*/

char	*get_pwd(void);

/*
**	Dans search_path.c : (Permet une recherche dans une variable de type $PATH)
*/
char	*search_path(char *path, char *name, int mode);

/*
**	Dans make_canonical.c : (utilisée par cd pour simplifier un path)
*/
int		make_canonical(char *s);

/*
**	Dans display_utils.c : (affichages divers)
*/
char	*ft_cat3(char *s1, char *s2, char *s3);
int		ft_err4(char *s1, char *s2, char *s3, char *s4);

/*
**	Dans tmp_utils.c : (créqation de fichiers temporaires)
*/

char	*tmp_name(char *path);

int		heredoc(t_red *red);

/*
**	Dans apply_redir.c :
*/

int		apply_redir(t_cmd *cmd);

#endif
