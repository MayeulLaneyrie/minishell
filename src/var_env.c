#include "../include/minishell.h"

/*
**	Verifie le nombre de variable d'environnement a remplacer.
*/
int	check_var_exp(char *s)
{
	int	i;
	int	num_dollar;

	i = 0;
	num_dollar = 0;
	while (s[i])
	{
		if (s[i] == '$')
			num_dollar++;
		i++;
	}
	return (num_dollar);
}

/*
**	Creer une string contenant la variable d'env a trouver dans env
**	afin de l'utiliser dans get_var.
*/
char	*create_tmp(char *s, int i)
{
	char	*dest;
	int		j;
	int		i_tmp;

	j = 0;
	i_tmp = i;
	while (s[i] != ' ' && s[i] != '"' && s[i])
		i++;
	dest = (char *)malloc(sizeof(char) * i);
	if (!dest)
		return (NULL);
	i = i_tmp + 1;
	if (s[i] == '$')
	{
		dest[j] = '\0';
		return (dest);
	}
	while (s[i] != ' ' && s[i] != '"' && s[i])
		dest[j++] = s[i++];
	dest[j] = '\0';
	return (dest);
}

/*
**	Remplace dans une string la premiere variable d'environnement rencontree.
**	old_rdl : adresse de la string a modifier
**	var_env : resultat de la variable d'environnement a modifier
**	len : taille de var_env
**	retour : string nouvellement modifiee ou NULL le cas echeant.
*/
char	*create_new_rdl(char **old_rdl, char *var_env, int len)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!var_env)
		dest = (char *)malloc(sizeof(char) * (ft_strlen(*old_rdl) - len + 1));
	else
		dest = (char *)malloc(sizeof(char) * (ft_strlen(*old_rdl) - len
					+ ft_strlen(var_env) + 1));
	if (!dest)
		return (NULL);
	while (old_rdl[0][i] != '$' && old_rdl[0][i])
		dest[j++] = old_rdl[0][i++];
	if (old_rdl[0][i] == '$' && var_env != NULL)
		while (*var_env)
			dest[j++] = *var_env++;
	while (old_rdl[0][i] != ' ' && old_rdl[0][i] != '"' && old_rdl[0][i])
		i++;
	while (old_rdl[0][i])
		dest[j++] = old_rdl[0][i++];
	return (dest[j] = '\0', free(*old_rdl), dest);
}

/*
**	Fonction servant a passer la norme (nombre de lignes)...
*/
int	norm_win_lines(char *stck_var_env, char **s, char **tmp, t_sh *sh)
{
	free (*s);
	*s = create_new_rdl(tmp, get_var(sh->env, stck_var_env),
			(ft_strlen(stck_var_env) + 1));
	if (!*s)
		return (MALLOC_ERROR);
	*tmp = ft_strdup(*s);
	free(stck_var_env);
	return (0);
}

/*
**	Description - Remplace toutes les variables d'environnement d'une string.
**	t_sh *sh - Structure avec l'env complet du projet
**  char **s - Adresse du retour d'un readline
**	Retour - 0 en cas de succes ou un code d'erreur le cas echeant 
*/
int	switch_var(t_sh *sh, char **s)
{
	int		i;
	char	*stck_var_env;
	char	*tmp;
	int		quoted;

	i = -1;
	quoted = 0;
	tmp = ft_strdup(*s);
	while (s[0][++i])
	{
		if (s[0][i] == '\'' && !quoted)
			quoted = 1;
		else if (s[0][i] == '\'' && quoted)
			quoted = 0;
		if (s[0][i] == '$' && !quoted)
		{
			stck_var_env = create_tmp(*s, i);
			if (norm_win_lines(stck_var_env, s, &tmp, sh) == MALLOC_ERROR)
				return (MALLOC_ERROR);
			i = -1;
		}
	}
	return (free(tmp), 0);
}
