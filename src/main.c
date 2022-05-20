#include "../include/minishell.h"

int	g_xt_stat = 0;

int	sh_debug(t_sh *sh)
{
	t_cmd	**cmd;

	if (!sh)
		return (printf("SH IS NULL\n"));
	if (!sh->pipeline)
		return (printf("PIPELINE IS NULL\n"));
	cmd = (t_cmd **)sh->pipeline->data;
	printf
	(
		"================\n\"%s\" DEBUG INFO (%d CMD)\n================\n",
		sh->exec_name, sh->pipeline->len
	);
	for (int i = 0; i < sh->pipeline->len; i++)
	{
		printf("CMD #%d: [%s]\n", i, cmd[i]->av[0]);
		for (int j = 1; j < cmd[i]->ac; j++)
			printf("    AV[%d]: %s\n", j, cmd[i]->av[j]);
		if (i != sh->pipeline->len - 1)
			printf("----------------\n");
	}
	printf("================\n");
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_sh	sh;

	printf("Welcome to minishell \"MarkIII\"!\n");
	if (new_sh(ac, av, envp, &sh) < 0)
		return (-1);
	while (1)
	{
		if (main_part1(&sh))
			break ;
		//sh_debug(&sh);
		if (main_part2(&sh))
			break ;
		del_split(sh.pipeline, &del_cmd);
		sh.pipeline = NULL;
	}
	del_sh(&sh);
	clear_history();
	return (g_xt_stat);
}
