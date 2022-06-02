/*
**	structures.h est le lieu dedié pour définir des structures custom,
**	en particulier si d'autres fichiers .h y font référence
*/

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <stdbool.h>

/*
**	data : un void** pouvant pointer vers n'importe quel type de données.
**	size : la capacité maximale du split.
**	len : le nombre de pointeur réellement stockés.
**	
**	Toute fonction modifiant un t_split doit garantir que len ne sera jamais
**	supérieur à size. On pourra éventuellement remplacer data pour stocker plus
**	de données.
*/
typedef struct s_split
{
	void	**data;
	int		size;
	int		len;
}	t_split;

/*
**	s_list : liste doublement chainee contenant une data
**	 ainsi que l'adresse de la donnee precedante et suivante.
*/
typedef struct s_list
{
	void			*data;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

/*
**	'in_out' can be RED_IN or RED_OUT, 'mode' can be RED_TRUNC or RED_APPEND.
*/
typedef struct s_red
{
	int		fd;
	int		in_out;
	int		mode;
	char	*word;
}	t_red;

typedef struct s_cmd
{
	int		pid;
	int		builtin_id;
	char	*path;
	int		ac;
	char	**av;
	int		is_piped[2];
	int		pipe_in[2];
	int		pipe_out[2];
	t_list	*red;
}	t_cmd;

/*
**	cmd : une commande simple parsée.
**	xt_stat : Le statut de sortie de la dernière tache exécutée. xt_stat devrait
**		être la valeur de retour de main().
*/
typedef struct s_sh
{
	char			*exec_name;
	t_split			*env;
	t_split			*pipeline;
}	t_sh;

/*
**	Type de données pour stocker les fonctions liées aux builtins.
*/
typedef int	(*t_bi)(t_sh *sh, t_cmd *cmd);

#endif
