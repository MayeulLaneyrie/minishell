#include "../include/minishell.h"

char	*get_var(char **envp, char *name)
{
	int	i;
	int	l;

	if (!name || !envp)
		return (NULL);
	l = ft_strlen(name);
	i = -1;
	while (envp[++i])
		if (!ft_strncmp(envp[i], name, l))
			break ;
	if (!envp[i])
		return (envp[i]);
	return (envp[i] + l + 1);
}
