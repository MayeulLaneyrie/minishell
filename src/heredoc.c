/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:46:46 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/06/02 16:46:50 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	increment_char(char *s, int index, char min, char max)
{
	s[index]++;
	if (s[index] <= max)
		return (0);
	s[index] = min;
	if (!index)
		return (1);
	return (increment_char(s, index - 1, min, max));
}

char	*tmp_name(char *dir)
{
	int		l;
	char	*ret;
	int		end;

	if (access(dir, R_OK | W_OK | X_OK))
		return (NULL);
	l = ft_strlen(dir);
	ret = malloc(l + 20);
	if (!ret)
		exit(EXIT_FAILURE);
	ret[0] = '\0';
	ft_strlcat(ret, dir, l + 2);
	ft_strlcat(ret, "/minishell_AAAA", l + 19);
	l += 11;
	end = 0;
	while (!end)
	{
		if (access(ret, F_OK))
			break ;
		end = increment_char(ret + l, 3, 'A', 'Z');
	}
	if (!access(ret, F_OK))
		return (ft_free(ret));
	return (ret);
}

int	rw_line(int fd, char *word, int l)
{
	char	*line;

	line = readline("> ");
	if (!ft_strncmp(line, word, l + 1))
	{
		free(line);
		return (1);
	}
	if (line)
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	return (0);
}

int	heredoc(t_red *red)
{
	char	*tmp_file;
	char	*line;
	int		l;
	int		fd;

	tmp_file = tmp_name("/tmp");
	if (!tmp_file)
		return (ft_puts("minishell: heredoc tmp file can't be created", 2) - 1);
	fd = open(tmp_file, O_WRONLY | O_CREAT, 0666);
	if (!fd)
		return (ft_puts("minishell: heredoc tmp file can't be created", 2)
			- 1 + (long)ft_free(tmp_file));
	line = NULL;
	l = ft_strlen(red->word);
	while (!rw_line(fd, red->word, l))
		;
	free(red->word);
	red->word = tmp_file;
	close(fd);
	return (0);
}
