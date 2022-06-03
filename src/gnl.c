/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrah <bifrah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 15:56:48 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/06/03 16:27:23 by bifrah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	buffer_len(char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len] && s[len] != '\n')
		len++;
	return (len);
}

static char	*buffer_join(char *buffer, char *line)
{
	size_t	i;
	size_t	j;
	char	*ret;

	i = buffer_len(buffer) + buffer_len(line);
	ret = malloc(i + 1);
	if (!ret)
		return (NULL);
	i = 0;
	while (line[i])
	{
		ret[i] = line[i];
		i++;
	}
	j = 0;
	while (buffer[j] && buffer[j] != '\n')
	{
		ret[i] = buffer[j];
		i++;
		j++;
	}
	ret[i] = '\0';
	return (ret);
}

static int	flush_buffer(char *buffer, char **line)
{
	size_t	i;
	size_t	j;
	int		ret;
	char	*temp;

	temp = buffer_join(buffer, *line);
	if (!temp)
	{
		free(*line);
		*line = NULL;
		return (0);
	}
	free(*line);
	*line = temp;
	j = 0;
	while (buffer[j] && buffer[j] != '\n')
		j++;
	ret = (buffer[j] == '\n');
	i = 0;
	while (buffer[j])
		buffer[i++] = buffer[++j];
	return (ret);
}

static int	panic_free(char **s)
{
	free(*s);
	*s = NULL;
	return (-1);
}

int	get_next_line(char **line)
{
	static char	buff[GNL_BUFFER_SIZE + 2] = {0};
	int			n;

	if (!line)
		return (-1);
	*line = malloc(1);
	if (!*line)
		return (-2);
	**line = '\0';
	n = 1;
	while (!flush_buffer(buff, line) && n)
	{
		if (!*line)
			return (panic_free(line));
		n = read(0, buff, GNL_BUFFER_SIZE);
		if (n < 0)
			return (panic_free(line));
		buff[n] = '\0';
	}
	return ((n > 0) - (n == -1));
}
