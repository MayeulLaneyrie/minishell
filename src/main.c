#include "../include/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_sh	*sh;
	int		ret;

	(void)ac;
	(void)av;
	printf("Welcome to minishell \"MarkI\"!\n");
	sh = new_sh(envp);
	if (!sh)
		return (-1);
	while (!main_part1(sh))
	{
		if (main_part2(sh))
			break ;
	}
	ret = sh->xt_stat;
	del_sh(&sh);
	return (ret);
}
