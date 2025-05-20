/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 16:18:43 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/06/08 04:37:50 by lnr              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_reg(char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	return (S_ISREG(path_stat.st_mode));
}

char	*search_through_dirs(t_split *dirs, char *name, int cd)
{
	int		i;
	char	*temp;

	i = -1;
	while (dirs->data[++i])
	{
		if (!dirs->data[i] && cd)
			temp = ft_cat3(".", "/", name);
		else
			temp = ft_cat3(dirs->data[i], "/", name);
		if (!temp)
			exit(EXIT_FAILURE);
		if (!access(temp, F_OK) && is_reg(temp))
			return (temp + (unsigned long)del_split(dirs, &ft_free));
		free(temp);
	}
	del_split(dirs, &ft_free);
	return (NULL);
}

char	*search_path(char *path, char *name, int cd)
{
	t_split	*dirs;

	if (!path)
		path = ft_strdup("/bin");
	if (!path)
		return (NULL);
	dirs = ft_split(path, ':');
	if (!dirs)
		return (NULL);
	return (search_through_dirs(dirs, name, cd));
}
