#include "../include/minishell.h"

int	g_xt_stat = 0;

int	sh_debug(t_sh *sh)
{
	t_cmd	**cmd;
	int		i;
	int		j;

	if (!sh)
		return (printf("SH IS NULL\n"));
	if (!sh->pipeline)
		return (printf("PIPELINE IS NULL\n"));
	cmd = (t_cmd **)sh->pipeline->data;
	printf(
		"================\n\"%s\" DEBUG INFO (%d CMD)\n================\n",
		sh->exec_name, sh->pipeline->len);
	i = -1;
	while (++i < sh->pipeline->len)
	{
		printf("CMD #%d: [%s]\n", i, cmd[i]->av[0]);
		j = 0;
		while (++j < cmd[i]->ac)
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
		write(1, "VOILA\n", 6);
		if (main_part2(&sh))
			break ;
		del_split(sh.pipeline, &del_cmd);
		sh.pipeline = NULL;
	}
	del_sh(&sh);
	clear_history();
	return (g_xt_stat);
}
