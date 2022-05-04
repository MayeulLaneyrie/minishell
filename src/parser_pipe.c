#include "../include/minishell.h"

/*
**	parse_cmd02 parse a la maniere de parse_cmd le contenu de chaques pipe.
**	C'est a dire, une seule commande, ses options et ses arguments.
**	une fois parse, le tout est stocke dans ***.
*/
int	parse_cmd02(char *s, t_sh **sh)
{
	t_split	*tmp;
	int		n;

	n = -1;
	tmp = quote_split(s, '|');
	if (!tmp)
		return (-1);
	sh[0]->pipeline = new_split(tmp->len);
	if (!sh[0]->pipeline)
		return (-2);
	sh[0]->pipeline->len = tmp->len;
	while (tmp->data[++n])
	{
		sh[0]->pipeline->data[n] = new_cmd();
		if (!sh[0]->pipeline->data[n])
			return (-3);
		parse_cmd(tmp->data[n], sh);
	}
	del_split(tmp, &ft_free);
	return (0);
}