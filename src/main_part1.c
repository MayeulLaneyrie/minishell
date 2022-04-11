#include "../include/minishell.h"

void	clean_d_quote(t_sh *sh)
{
	int		i;
	int		j;
	char	*tmp;

	j = 0;
	while (sh->cmd->av[j])
	{
		i = 0;
		if (sh->cmd->av[j][i] == '"'
			&& sh->cmd->av[j][ft_strlen(sh->cmd->av[j])] == '"')
		{
			tmp = (char *)malloc(sizeof(char) * ft_strlen(sh->cmd->av[j]) - 2);
			while (sh->cmd->av[j][i + 1])
			{
				tmp[i] = sh->cmd->av[j][i + 1];
				i++;
			}
			free(sh->cmd->av[j]);
			sh->cmd->av[j] = NULL;
			sh->cmd->av[j] = ft_strdup(tmp);
			free(tmp);
		}
		j++;
	}
}

void	word_cpy(t_sh *sh, t_rl *rl, int i, int j)
{
	int	k;

	k = 0;
	rl->d_quote = false;
	rl->quote = false;
	if (rl->rdline[i] != '"' && rl->rdline[i] != '\'')
	{
		while (rl->rdline[i] && !(is_meta(rl->rdline[i]))
			&& (rl->d_quote == false || rl->quote == false))
		{
			sh->cmd->av[j][k++] = rl->rdline[i++];
			if (rl->rdline[i] == '"' && rl->d_quote == false
				&& is_meta(rl->rdline[i - 1]))
				rl->d_quote = true;
			if (rl->rdline[i] == '\'' && rl->quote == false
				&& is_meta(rl->rdline[i - 1]))
				rl->quote = true;
		}
	}
	else if (rl->d_quote == true && rl->d_quote == false && rl->quote == false)
	{
		rl->d_quote = true;
		while (rl->rdline[i] != '"' && rl->d_quote == true)
		{
			sh->cmd->av[j][k++] = rl->rdline[i++];
			if (rl->rdline[i] == '"')
				rl->d_quote = false;
		}
	}
	else if (rl->quote == true && rl->d_quote == false && rl->quote == false)
	{
		rl->quote = true;
		while (rl->rdline[i] != '\'' && rl->quote == true)
		{
			sh->cmd->av[j][k++] = rl->rdline[i++];
			if (rl->rdline[i] == '\'')
				rl->quote = false;
		}
	}
}

int	word_len(t_rl *rl, int i)
{
	int		tmp;

	tmp = i;
	rl->d_quote = false;
	rl->quote = false;
	if (rl->rdline[i] != '"' && rl->rdline[i] != '\'')
	{
		while (rl->rdline[i] && !(is_meta(rl->rdline[i]))
			&& (rl->d_quote == false || rl->quote == false))
		{
			i++;
			if (rl->rdline[i] == '"' && rl->d_quote == false
				&& is_meta(rl->rdline[i - 1]))
				rl->d_quote = true;
			if (rl->rdline[i] == '\'' && rl->quote == false
				&& is_meta(rl->rdline[i - 1]))
				rl->quote = true;
		}
	}
	else if (rl->d_quote == true && rl->d_quote == false && rl->quote == false)
	{
		rl->d_quote = true;
		while (rl->rdline[i] != '"' && rl->d_quote == true)
		{
			i++;
			if (rl->rdline[i] == '"')
				rl->d_quote = false;
		}
	}
	else if (rl->quote == true && rl->d_quote == false && rl->quote == false)
	{
		rl->quote = true;
		while (rl->rdline[i] != '\'' && rl->quote == true)
		{
			i++;
			if (rl->rdline[i] == '\'')
				rl->quote = false;
		}
	}
	return (i - tmp);
}

int	fill_cmd(t_sh *sh, t_rl *rl)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	write(1, "i'm in fill_cmd\n", 16);
	while (rl->rdline[i])
	{
		while (is_meta(rl->rdline[i]) == true)
			i++;
		realloc_split(sh, rl, i);
		word_cpy(sh, rl, i, j);
		i += word_len(rl, i);
		j++;
	}
	clean_d_quote(sh);
	return (0);
}

int	main_part1(t_sh *sh)
{
	t_rl	rl;
	int		ret;

	(void)sh;
	ret = 0;
	rl.rdline = readline("[Minishell MkI] ");
	if (rl.rdline == NULL)
		return (NULL_RDLINE);
	if (count_quote(rl.rdline) == -1)
		return (WRONG_NB_QUOTE);
	else if (rl.rdline[0] == '\0')
	{
		sh->cmd = new_cmd();
		sh->cmd->av = new_av(sh->cmd);
		free (rl.rdline);
	}
	else
	{
		sh->cmd = new_cmd();
		if (find_d_quote(rl.rdline) == false)
		{
			sh->cmd->av = ft_split_b(rl.rdline, ' ');
			sh->cmd->ac = ac_of_av(sh->cmd->av);
			free (rl.rdline);
		}
		else
		{
			ret = fill_cmd(sh, &rl);
			if (ret != 0)
				return (1);
		}
	}
	return (0);
}

/*
**	En construcion, pour faire fonctionner le programme en attendant,
**	Modifier la ligne 177 par "if (1)" pour eviter d'entrer dans le else.
*/
		// printf("av[0] = %s\n", sh->cmd->av[0]);