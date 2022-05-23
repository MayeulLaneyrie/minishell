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
	// if (s[i] == '?')
	// {
	// 	dest = ft_itoa(g_xt_stat);
	// 	return (dest);
	// }
	while (s[i] != ' ' && s[i] != '"' && s[i])
		dest[j++] = s[i++];
	dest[j] = '\0';
	return (dest);
}

/*
**	Remplace dans une string la premiere
**	variable d'environnement rencontree.
*/
char	*create_new_rdl(char **old_rdl, char *stck_exp, int len)
{
	char	*dest;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	if (!stck_exp)
		dest = (char *)malloc(sizeof(char) * (ft_strlen(*old_rdl) - len + 1));
	else
		dest = (char *)malloc(sizeof(char) * (ft_strlen(*old_rdl) - len
					+ ft_strlen(stck_exp) + 1));
	if (!dest)
		return (NULL);
	while (old_rdl[0][i] != '$' && old_rdl[0][i])
		dest[j++] = old_rdl[0][i++];
	if (old_rdl[0][i] == '$' && stck_exp != NULL)
	{
		while (stck_exp[k])
			dest[j++] = stck_exp[k++];
	}
	while (old_rdl[0][i] != ' ' && old_rdl[0][i] != '"' && old_rdl[0][i])
		i++;
	while (old_rdl[0][i])
		dest[j++] = old_rdl[0][i++];
	dest[j] = '\0';
	free(*old_rdl);
	return (dest);
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
	char	*stck_exp;
	char	*tmp;
	int		quoted;

	i = 0;
	quoted = 0;
	tmp = ft_strdup(*s);
	while (s[0][i])
	{
		if (s[0][i] == '\'' && !quoted)
			quoted = 1;
		else if (s[0][i] == '\'' && quoted)
			quoted = 0;
		if (s[0][i] == '$' && !quoted)
		{
			stck_exp = create_tmp(*s, i);
			free (*s);
			*s = create_new_rdl(&tmp, get_var(sh->env, stck_exp),
					(ft_strlen(stck_exp) + 1));
			if (!*s)
				return (MALLOC_ERROR);
			tmp = ft_strdup(*s);
			free(stck_exp);
			i = 0;
		}
		i++;
	}
	free(tmp);
	return (0);
}
