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

int	cnf_handler(t_sh *sh, t_cmd *cmd)
{
	char	*s;
	int		l;

	l = ft_strlen(cmd->av[0]) + 21;
	s = malloc(l + 1);
	if (!s)
		return (-1);
	s[0] = 0;
	ft_strlcat(s, cmd->av[0], l);
	ft_strlcat(s, ": command not found\n", l);
	write(2, s, l);
	free(s);
	sh->xt_stat = 128;
	return (-1);
}

char	*search_path(char *path, char *name)
{
	t_split	*dirs;
	char	*temp;
	int		i;
	// int		l;

	dirs = ft_split(path, ':');
	if (!dirs)
		return (NULL);
	// l = ft_strlen(name);
	i = -1;
	while (dirs->data[++i])
	{
		temp = ft_cat3(dirs->data[i], "/", name);
		if (!temp)
			return (NULL);
		if (!access(temp, F_OK))
			return (temp + (unsigned long)del_split(&dirs));
		free(temp);
	}
	del_split(&dirs);
	return (NULL);
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
			return (cnf_handler(sh, cmd));
	}
	printf("EXECVE %s:\n", cmd_path);
	execve(cmd_path, cmd->av, sh->envp);
	printf("\tFAILED !\nAV:\n");
	for (int i = 0; i < cmd->ac; i++)
		printf("\t%s\n", cmd->av[i]);
	printf("CAUSE: %s\n", strerror(errno));
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
	waitpid(pid, NULL, 0);
	return (0);
}
