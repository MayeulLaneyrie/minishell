/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:31:35 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/06/02 16:31:37 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_echo_opt(t_cmd *cmd)
{
	int	opt;
	int	i;

	opt = 0;
	i = 1;
	if (cmd->ac > 1 && cmd->av[1][0] == '-')
	{
		while (cmd->av[1][i] && cmd->av[1][i] == 'n')
			i++;
		if (i > 1 && !cmd->av[1][i])
			opt = 1;
	}
	return (opt);
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
	display[size - 1] = '\n';
	write(1, display, size - opt);
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
		return (0 * write(1, "\n", 1 - opt));
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
