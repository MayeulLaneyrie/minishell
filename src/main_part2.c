/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_part2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 21:01:52 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/03/18 18:40:15 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_cat3(char *s1, char *s2, char *s3)
{
	char	*ret;
	int		size;

	size = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1;
	ret = malloc(size);
	if (!ret)
		return (NULL);
	ret[0] = 0;
	ft_strlcat(ret, s1, size);
	ft_strlcat(ret, s2, size);
	ft_strlcat(ret, s3, size);
	return (ret);
}

char	*search_path(char *path, char *name)
{
	char	**dirs;
	char	*temp;
	int		i;
	int		l;

	dirs = ft_split(path, ':');
	if (!dirs)
		return (NULL);
	l = ft_strlen(name);
	i = -1;
	while (dirs[++i])
	{
		temp = ft_cat3(dirs[i], "/", name);
		if (!temp)
			return (NULL);
		if (!access(temp, F_OK))
			return (temp);//TODO: fix memleak on dirs 
		free(temp);
	}
	return (NULL);//TODO: same
}

int	cmd_proc(t_sh *sh, t_cmd *cmd)
{
	char	*cmd_path;

	cmd_path = cmd->av[0];
	if (!ft_strchr(cmd_path, '/'))
	{
		//TODO: search builtin
		cmd_path = search_path(get_var(sh->envp, "PATH"), cmd_path);
		if (!cmd_path)
		{
			sh->xt_stat = 128;
			return (-1);
		}
	}
	execve(cmd_path, cmd->av, sh->envp);
	return (-1);
}

int	main_part2(t_sh *sh)
{
	int		pid;

	pid = fork();
	if (!pid)
		return (cmd_proc(sh, sh->cmd));
	del_cmd(&sh->cmd);
	if (pid < 0)
		return (-1);
	return (0);
}
