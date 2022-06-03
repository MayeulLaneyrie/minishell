/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrah <bifrah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 16:26:16 by bifrah            #+#    #+#             */
/*   Updated: 2022/06/03 16:27:21 by bifrah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int		ret_main1;

	sig_init(SIGINT, SIG_IGN);
	sig_init(SIGQUIT, SIG_IGN);
	if (!envp)
		exit (EXIT_FAILURE);
	if (new_sh(ac, av, envp, &sh) < 0)
		return (-1);
	if (isatty(0))
		printf("Welcome to minishell \"Endgame\"!\n");
	while (1)
	{
		ret_main1 = main_part1(&sh);
		if (ret_main1 > -4 && ret_main1 < 0)
			break ;
		if (ret_main1 != -4 && main_part2(&sh))
			break ;
		del_split(sh.pipeline, &del_cmd);
		sh.pipeline = NULL;
	}
	del_sh(&sh);
	clear_history();
	return (g_xt_stat);
}
