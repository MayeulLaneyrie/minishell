#include "../include/minishell.h"

int	ac_of_av(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}

char	**create_tmp(char **av)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = (char **)malloc(sizeof(char *) * ac_of_av(av) + 1);
	if (!tmp)
		return (NULL);
	while (av[i])
	{
		tmp[i] = ft_strdup(av[i]);
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}

bool	realloc_tab(t_sh *sh, t_rl *rl, int i)
{
	char	**tmp;
	int		k;

	k = 0;
	if (sh->cmd->av)
	{
		tmp = create_tmp(sh->cmd->av);
		free_split_b(sh->cmd->av);
		sh->cmd->av = (char **)malloc(sizeof(char *) * (ac_of_av(tmp) + 2));
		if (!sh->cmd->av)
			return (MALLOC_ERROR);
		while (tmp[k])
		{
			sh->cmd->av[k] = ft_strdup(tmp[k]);
			k++;
		}
		sh->cmd->av[k] = (char *)malloc(sizeof(char) * word_len(rl, i) + 1);
		sh->cmd->av[k] = NULL;
		sh->cmd->av[k + 1] = (char *)malloc(sizeof(char) * 1);
		sh->cmd->av[k + 1] = NULL;
		sh->cmd->ac += 2;
		free_split_b(tmp);
		return (1);
	}
	return (0);
}
