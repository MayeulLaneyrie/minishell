/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 16:18:43 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/06/04 16:21:26 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_reg(char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	return (S_ISREG(path_stat.st_mode));
}

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
		if (!access(temp, F_OK) && is_reg(temp))
			return (temp + (unsigned long)del_split(dirs, &ft_free));
		free(temp);
	}
	del_split(dirs, &ft_free);
	return (NULL);
}
