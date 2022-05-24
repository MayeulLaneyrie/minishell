#include "../include/minishell.h"

char	*search_path(char *path, char *name, int cd)
{
	t_split	*dirs;
	char	*temp;
	int		i;

	if (!path)
		return (NULL);
	dirs = ft_split(path, ':');
	if (!dirs)
		return (NULL);
	i = -1;
	while (dirs->data[++i])
	{
		if (!dirs->data[i] && cd)
			temp = ft_cat3(".", "/", name);
		else
			temp = ft_cat3(dirs->data[i], "/", name);
		if (!temp)
			exit(EXIT_FAILURE);
		if (!access(temp, F_OK))
			return (temp + (unsigned long)del_split(dirs, &ft_free));
		free(temp);
	}
	del_split(dirs, &ft_free);
	return (NULL);
}
