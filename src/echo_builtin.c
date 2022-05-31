#include "../include/minishell.h"

int	bi_echo(t_sh *sh, t_cmd *cmd)
{
	int		opt;
	int		size;
	char	*display;
	int		i;

	(void)sh;
	g_xt_stat = 0;
	i = 1;
	opt = 0;
	if (cmd->ac > 1 && cmd->av[1][0] == '-')
	{
		while (cmd->av[1][i] && cmd->av[1][i] == 'n')
			i++;
		if (i > 1 && !cmd->av[1][i])
			opt = 1;
	}
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
	display[0] = '\0';
	i = opt;
	while (++i < cmd->ac)
	{
		ft_strlcat(display, cmd->av[i], size);
		ft_strlcat(display, " ", size);
	}
	display[size - 1] = '\n';
	write(1, display, size - opt);
	return (0);
}
