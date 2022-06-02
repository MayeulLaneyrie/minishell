/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_subst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 22:06:22 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/06/02 22:11:51 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_id_len(char *s, int i)
{
	int	ret;

	i++;
	ret = 0;
	if (s[i] == '?')
		return (1);
	if (!ft_isalpha(s[i]) && s[i] != '_')
		return (0);
	while (ft_isalnum(s[i + ret]) || s[i + ret] == '_')
		ret++;
	return (ret);
}

char	*get_subst(t_split *env, char *id)
{
	char	*ret;
	char	*tmp;

	if (id[0] == '?' && id[1] == '\0')
	{
		ret = ft_itoa(g_xt_stat);
		if (!ret)
			return (NULL);
	}
	else
	{
		tmp = get_var(env, id);
		if (!tmp)
			ret = malloc(1);
		else
			ret = ft_strdup(tmp);
		if (!ret)
			return (NULL);
		if (!tmp)
			ret[0] = '\0';
	}
	return (ret);
}

int	apply_subst(char **s, int i, int id_len, char *subst)
{
	int		old_len;
	int		subst_len;
	char	*new;

	subst_len = ft_strlen(subst);
	old_len = ft_strlen(*s);
	if (subst_len > id_len)
	{
		new = malloc(old_len + subst_len - id_len);
		if (!new)
			return ((long)ft_free(subst) - 1);
		ft_strlcpy(new, *s, i + 1);
	}
	else
		new = *s;
	ft_strlcpy(new + i, subst, subst_len + 1);
	free(subst);
	ft_strlcpy(new + i + subst_len, *s + i + id_len + 1,
		old_len + subst_len - id_len);
	if (subst_len > id_len)
		free(*s);
	*s = new;
	return (i + subst_len);
}

int	single_dollar_subst(t_split *env, char **s, int i)
{
	char	*id;
	int		id_len;
	char	*subst;

	while ((*s)[i] && (*s)[i] != '$')
		i++;
	id_len = get_id_len(*s, i);
	if (!id_len)
		return (i + 1);
	id = malloc(id_len + 1);
	if (!id)
		return (-1);
	ft_strlcpy(id, *s + i + 1, id_len + 1);
	subst = get_subst(env, id);
	free(id);
	if (!subst)
		return (-1);
	return (apply_subst(s, i, id_len, subst));
}

char	*all_dollar_subst(t_split *env, char *s)
{
	int	i;
	int	quote;
	int	d_quote;

	i = 0;
	quote = 0;
	d_quote = 0;
	while (s[i])
	{
		if (s[i] == '"' && !quote && !d_quote)
			d_quote = 1;
		else if (s[i] == '"' && d_quote)
			d_quote = 0;
		else if (s[i] == '\'' && !quote && !d_quote)
			quote = 1;
		else if (s[i] == '\'' && quote)
			quote = 0;
		else if (s[i] == '$' && !quote)
			i = single_dollar_subst(env, &s, i) - 1;
		if (i < 0)
			return (ft_free(s));
		i++;
	}
	return (s);
}
