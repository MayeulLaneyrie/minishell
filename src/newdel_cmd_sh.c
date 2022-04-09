#include "../include/minishell.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*ret;

	ret = malloc(sizeof(t_cmd));
	if (!ret)
		return (NULL);
	ret->pid = 0;
	ret->builtin_id = -1;
	ret->path = NULL;
	ret->ac = 0;
	ret->av = NULL;
	return (ret);
}

void	*del_cmd(t_cmd **cmd)
{
	int	i;

	if (!cmd || !*cmd)
		return (NULL);
	if ((*cmd)->av)
	{
		i = -1;
		while (++i < (*cmd)->ac)
			ft_free((void **)&((*cmd)->av[i]));
		ft_free((void **)&((*cmd)->av));
	}
	ft_free((void **)&((*cmd)->path));
	ft_free((void **)cmd);
	return (NULL);
}

t_sh	*new_sh(int ac, char **av, char **envp)
{
	t_sh	*ret;

	(void)ac;
	if (!envp)
		return (NULL);
	ret = malloc(sizeof(t_sh));
	if (!ret)
		return (NULL);
	ret->exec_name = av[0];
	ret->envp = envp;
	ret->cmd = NULL;
	ret->xt_stat = 0;
	return (ret);
}

void	*del_sh(t_sh **sh)
{
	if (!sh || !*sh)
		return (NULL);
	del_cmd(&(*sh)->cmd);
	free(*sh);
	*sh = NULL;
	return (NULL);
}
