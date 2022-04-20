#include "../include/minishell.h"

int	g_xt_stat = 0;

int	main(int ac, char **av, char **envp)
{
	t_sh	sh;

	printf("Welcome to minishell \"MarkII\"!\n");
	new_sh(ac, av, envp, &sh);
	while (!main_part1(&sh))
	{
		if (main_part2(&sh))
			break ;
		del_cmd(sh.cmd);
	}
	del_sh(&sh);
	clear_history();
	return (g_xt_stat);
}
