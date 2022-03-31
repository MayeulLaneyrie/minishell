#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_sh	*sh;

	(void)argc;
	(void)argv;
	write(0, "Welcome to minishell \"MarkI\"!\n", 30);
	sh = new_sh(envp);
	if (!sh)
		return (-1);
	while (!main_part1(sh))
	{
		if (main_part2(sh))
			break ;
	}
	del_sh(&sh);
	return (0);
}
