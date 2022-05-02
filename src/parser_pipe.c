#include "../include/minishell.h"

/*
**	pipe_len compte le nombre de caracteres a stocker avant le prochain pipe
*/
int	pipe_len(char *s)
{
	int	ret;
	int	quote;
	int	d_quote;

	ret = 0;
	quote = 0;
	d_quote = 0;
	while (*s && (*s != '|' || quote || d_quote))
	{
		if (*s == '"' && !quote && !d_quote)
			d_quote = 1;
		else if (*s == '"' && d_quote)
			d_quote = 0;
		else if (*s == '\'' && !quote && !d_quote)
			quote = 1;
		else if (*s == '\'' && quote)
			quote = 0;
		else
			ret++;
		s++;
	}
	return (ret);
}

/*
**	pipe_cpy stocke dans un char * une commande, ses option et ses arguments
*/
int	pipe_cpy(char *dst, char *src)
{
	int	i;
	int	quote;
	int	d_quote;

	i = 0;
	quote = 0;
	d_quote = 0;
	while (src[i] && (src[i] != '|' || quote || d_quote))
	{
		if (src[i] == '"' && !quote && !d_quote)
			d_quote = 1;
		else if (src[i] == '"' && d_quote)
			d_quote = 0;
		else if (src[i] == '\'' && !quote && !d_quote)
			quote = 1;
		else if (src[i] == '\'' && quote)
			quote = 0;
		else
		{
			*dst = src[i];
			dst++;
		}
		i++;
	}
	*dst = '\0';
	return (i);
}

/*
**	cut_pipe separe le retour de readline en une liste contenant pour chaque pipe
**	une data cense etre la commande, ses options et ses arguments
**	que l'on doit ensuite parser pour attester d'une commande valide.
*/
t_list	*cut_pipe(char *s)
{
	int		l;
	char	*w;
	t_list	*ret;

	ret = NULL;
	while (*s)
	{
		while (ft_strchr(METACHAR, *s))
			s++;
		l = pipe_len(s);
		w = malloc(l + 1);
		if (!w)
			return (ft_lstclear(&ret, &free));
		s += pipe_cpy(w, s);
		if (!ft_lstadd_back(&ret, ft_lstnew(w)))
			return (ft_lstclear(&ret, &free));
	}
	return (ret);
}

/*
**	parse_cmd02 parse a la maniere de parse_cmd le contenu de chaques pipe.
**	C'est a dire, une seule commande, ses options et ses arguments.
**	une fois parse, le tout est stocke dans ***.
*/
void	parse_cmd02(char *s, t_cmd **cmd)
{
	t_list	*word_list;
	t_split	*word_split;

	word_list = cut_pipe(s);
	if (!word_list)
		return (-1);
	while (word_list)
	{
		word_split = list_to_split(&word_list);
		if (!word_split)
			return (-3);
		(*cmd)->ac = word_split->len;
		(*cmd)->av = (char **)word_split->data;
		// ligne 111 : Dans quoi stocker ca ? afin de garder chaques av de chaques pipes
		free(word_split);
		word_list->next;
	}
}
