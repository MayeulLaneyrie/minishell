/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrah <bifrah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 16:26:27 by bifrah            #+#    #+#             */
/*   Updated: 2022/06/03 16:27:28 by bifrah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
**	check si les operateurs sont correctement utilise
**	prend en param s : la string a checker et &i l'adresse de l'index
**	return le mode de redirection  (APPEND or TRUNC), 0 en cas d'erreur
*/
int	check_redirect_operator(char *s, int *i)
{
	int	red;

	red = 0;
	if (s[*i] && s[*i] == '>')
		red = RED_OUT;
	else if (s[*i] && s[*i] == '<')
		red = RED_IN;
	(*i)++;
	if ((red == RED_OUT && s[*i] == '<') || (red == RED_IN && s[*i] == '>'))
		return (0);
	else
	{
		if (s[*i] == '<' && red == RED_IN)
		{
			(*i)++;
			return (RED_APPEND);
		}
		if (s[*i] == '>' && red == RED_OUT)
		{
			(*i)++;
			return (RED_APPEND);
		}
		return (RED_TRUNC);
	}
}

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

int	check_redirect(char *s, t_cmd *cmd, t_list *lst)
{
	int		i;
	t_red	*tmp;
	char	*new_word;
	int		j;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(t_red));
	if (!tmp)
		return (-1);
	if (s[i] == '>')
		tmp->in_out = RED_OUT;
	else if (s[i] == '<')
		tmp->in_out = RED_IN;
	tmp->mode = check_redirect_operator(s, &i);
	if (!tmp->mode)
		return (free(tmp), -2);
	tmp->fd = set_red_fd(tmp->in_out, lst);
	while (ft_strchr(SPACES, s[i]))
		i++;
	if (ft_strchr("<>", s[i]))
		return (-1);
	new_word = malloc(word_len(s + i) + 1);
	if (!new_word)
		return (free(tmp), -1);
	i += word_cpy(new_word, s + i);
	tmp->word = new_word;
	if (tmp->mode == RED_APPEND && tmp->in_out == RED_IN && heredoc(tmp) < 0)
		return (free(tmp), -1);
	if (!ft_lstadd_back(&(cmd->red), ft_lstnew(tmp)))
		return (free(tmp), (long)ft_lstclear(&cmd->red, &free) - 1);
	return (i);
}
