/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrah <bifrah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 16:56:33 by bifrah            #+#    #+#             */
/*   Updated: 2022/06/06 20:12:40 by bifrah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	set_red_fd(int in_out, t_list *lst)
{
	t_list			*head;
	int				i;
	char			*s;
	unsigned long	ret;

	head = ft_lstlast(lst);
	if (!head)
		return (in_out == RED_OUT);
	s = head->data;
	i = -1;
	while (s[++i])
		if (!ft_isdigit(s[i]))
			break ;
	if (s[i] || i > 10)
		return (in_out == RED_OUT);
	ret = ft_atoi(s);
	if (ret > 2147483647)
		return (in_out == RED_OUT);
	free(s);
	if (head->next)
		head->next->prev = NULL;
	if (head->prev)
		head->prev->next = NULL;
	free(head);
	return (ret);
}

void	skip_spaces(char *s, int *i)
{
	while (ft_strchr(SPACES, s[*i]))
		(*i)++;
}

int	in_or_out(char c)
{
	if (c == '>')
		return (RED_OUT);
	else if (c == '<')
		return (RED_IN);
	return (0);
}

void	fill_tmp_fd_mod_inout(t_red **tmp, char *s, int *i, t_list *lst)
{
	(*tmp)->in_out = in_or_out(s[*i]);
	(*tmp)->fd = set_red_fd((*tmp)->in_out, lst);
	(*tmp)->mode = check_redirect_operator(s, i);
}
