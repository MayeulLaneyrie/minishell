#include "../include/minishell.h"

t_split	*load_env(char **envp)
{
	t_split	*ret;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	ret = new_split(i);
	if (!ret)
		return (NULL);
	i = -1;
	while (++i < ret->size)
	{
		((char **)ret->data)[i] = ft_strdup(envp[i]);
		if (!ret->data[i])
			return (del_split(ret, &ft_free));
		ret->len++;
	}
	return (ret);
}

char	*get_var(t_split *env, char *name)
{
	int	i;
	int	l;

	if (!name || !env)
		return (NULL);
	l = ft_strlen(name);
	i = -1;
	while (++i < env->len)
		if (!ft_strncmp(((char **)env->data)[i], name, l))
			break ;
	if (!((char **)env->data)[i])
		return (((char **)env->data)[i]);
	return (((char **)env->data)[i] + l + 1);
}
