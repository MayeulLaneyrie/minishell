/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrah <bifrah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:28:02 by bifrah            #+#    #+#             */
/*   Updated: 2022/06/03 17:51:43 by bifrah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
**	print sur la sortie d'erreur une string constitue de 3 autres str attribue
	a la variable de retour d'erreur du bash une valeur oppose a celle choisie.
**	Pour correspondre au bash, la valeur doit etre inferieure a 0.
**	ex : si vous souhaitez retourner 127, il faut entrer -127.
**	new_g_xt_stat peut donc prendre en parametre une fonction retournant un int.
*/
void	printerror(char *str1, char *str2, char *str3, int new_g_xt_stat)
{
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
	ft_putstr_fd(str3, 2);
	g_xt_stat = -1 * new_g_xt_stat;
}
