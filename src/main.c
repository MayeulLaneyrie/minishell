/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrah <bifrah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:38:16 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/03/17 21:50:33 by bifrah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_sh	*sh;

	(void)argc;
	(void)argv;
	write(0, "Welcome to minishell \"MarkI\"!\n", 30);
	sh = new_sh();
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
