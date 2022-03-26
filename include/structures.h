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

typedef struct s_list
{
	void			*data;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

#endif
