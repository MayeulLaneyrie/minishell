/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrah <bifrah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:38:16 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/03/22 19:28:50 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
