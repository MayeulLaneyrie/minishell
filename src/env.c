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
		return (NULL);
	if (((char **)env->data)[i][l] != '=')
		return (NULL);
	return (((char **)env->data)[i] + l + 1);
}

int	set_var(t_split *env, char *name, char *value)
{
	char	*tmp;

	if (check_identifier(name, env, 0))
		return (-1);
	tmp = ft_cat3(name, "=", value);
	if (!tmp)
		exit(EXIT_FAILURE);
	export_single(env, tmp);
	free(tmp);
	return (0);
}

int	get_var_index(t_split *env, char *name)
{
	int	i;
	int	l;

	if (!name || !env)
		return (-42);
	l = -1;
	while (name[++l] != '=' && name[l])
		;
	i = -1;
	while (++i < env->len)
		if (!ft_strncmp(((char **)env->data)[i], name, l))
			break ;
	if (!((char **)env->data)[i])
		return (-1);
	if (((char **)env->data)[i][l] != '=')
		return (-1);
	return (i);
}
