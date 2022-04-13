#include "../include/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_sh	sh;
	int		ret;

	printf("Welcome to minishell \"MarkI\"!\n");
	new_sh(ac, av, envp, &sh);
	while (!main_part1(&sh))
	{
		if (main_part2(&sh))
			break ;
		del_cmd(&(sh.cmd));
	}
	ret = sh.xt_stat;
	del_sh(&sh);
	clear_history();
	return (ret);
}
