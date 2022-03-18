/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 03:34:21 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/03/18 03:53:15 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_var(char **envp, char *name)
{
	int	i;
	int	l;

	if (!name || !envp)
		return (NULL);
	l = ft_strlen(name);
	i = -1;
	while (envp[++i])
		if (!ft_strncmp(envp[i], name, l))
			break ;
	printf("SEARCH IS OVER : %s\n", envp[i]);
	if (!envp[i])
		return (envp[i]);
	printf("I SHOULD HAVE RETURNED NULL\n");
	return (envp[i] + l + 1);
}
