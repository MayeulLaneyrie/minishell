/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 16:15:36 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/06/08 17:06:51 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_echo_opt(t_cmd *cmd)
{
	int	leave;
	int	j;
	int	i;

	leave = 0;
	j = 1;
	while (!leave && j < cmd->ac)
	{
		leave = 1;
		if (cmd->ac > 1 && cmd->av[j][0] == '-')
		{
			i = 1;
			while (cmd->av[j][i] && cmd->av[j][i] == 'n')
				i++;
			if (i > 1 && !cmd->av[j][i])
				leave = 0;
		}
		if (!leave)
			j++;
	}
	return (j - 1);
}

int	echo_display(char *display, int opt, int size, t_cmd *cmd)
{
	int	i;

	display[0] = '\0';
	i = opt;
	while (++i < cmd->ac)
	{
		ft_strlcat(display, cmd->av[i], size);
		ft_strlcat(display, " ", size);
	}
	if (size)
		display[size - 1] = '\n';
	write(1, display, size - (opt != 0));
	free(display);
	return (0);
}

int	bi_echo(t_sh *sh, t_cmd *cmd)
{
	int		opt;
	int		size;
	char	*display;
	int		i;

	(void)sh;
	g_xt_stat = 0;
	opt = check_echo_opt(cmd);
	if (cmd->ac == 1 || (cmd->ac == 2 && opt))
		return (0 * write(1, "\n", 1 - (opt != 0)));
	if (opt == cmd->ac - 1)
		return (0);
	i = opt;
	size = 0;
	while (++i < cmd->ac)
	{
		size += ft_strlen(cmd->av[i]);
		size++;
	}
	display = malloc(size + 1);
	if (!display)
		exit(EXIT_FAILURE);
	return (echo_display(display, opt, size, cmd));
}
