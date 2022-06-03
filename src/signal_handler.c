/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:20:58 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/06/03 16:59:17 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sa_main_handler(int x)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_xt_stat = x + 128;
}

void	sa_stuff_handler(int x)
{
	write(1, "\n", 1);
	g_xt_stat = x + 128;
}

void	sa_child_handler(int x)
{
	exit(x + 128);
}

int	sig_init(int signo, void (*handler_fct)(int))
{
	struct sigaction	act;

	act.sa_handler = handler_fct;
	act.sa_flags = 0;
	sigemptyset(&(act.sa_mask));
	sigaction(signo, &act, NULL);
	return (0);
}
