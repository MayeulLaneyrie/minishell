/*
**	structures.h est le lieu dedié pour définir des structures custom,
**	en particulier si d'autres fichiers .h y font référence
*/

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <stdbool.h>

typedef struct s_cmd
{
	int		pid;
	int		builtin_id;
	char	*path;
	int		ac;
	char	**av;
}	t_cmd;

/*
**	cmd : une commande simple parsée.
**	xt_stat : Le statut de sortie de la dernière tache exécutée. xt_stat devrait
**		être la valeur de retour de main().
*/
typedef struct s_sh
{
	char			*exec_name;
	char			**envp;
	t_cmd			*cmd;
	unsigned char	xt_stat;
}	t_sh;

typedef int	(*t_bi)(t_sh *sh, t_cmd *cmd);

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

#endif
