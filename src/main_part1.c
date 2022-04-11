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

char	*word_cpy(t_rl *rl, int i)
{

}

int	word_len(t_rl *rl, int i)
{
	int	tmp;

	tmp = i;
	rl->d_quote = false;
	rl->quote = false;
	while (rl->rdline[i])
	{
		if (is_space(rl->rdline[i]))
			i++;
		if (rl->rdline[i] == '"' && i > 0 && is_space(rl->rdline[i - 1]))
		{
			rl->d_quote = true;
			i++;
			while (rl->rdline[i] != '"')
				i++;
			if (rl->rdline[i] == '"' && rl->d_quote == true)
				rl->d_quote = false;
			return (i - tmp - 2);
		}
		else if (rl->rdline[i] == '\'' && i > 0 && is_space(rl->rdline[i - 1]))
		{
			rl->quote = true;
			i++;
			while (rl->rdline[i] != '\'')
				i++;
			if (rl->rdline[i] == '\'' && rl->quote == true)
				rl->quote = false;
			return (i - tmp - 2);
		}
		else
		{
			while (!is_meta(rl->rdline[i]))
				i++;
			return (i - tmp);
		}
	}
}

int	fill_cmd(t_sh *sh, t_rl *rl)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (rl->rdline[i])
	{
		while (is_meta(rl->rdline[i]) == false)
			i++;
		word_cpy(sh, rl, i);
		if (is_space(rl->rdline[i]))
			i++;
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
		if (find_d_quote(rl.rdline) == false && find_quote(rl.rdline) == false)
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
			// printf("av[1] = %s\n", sh->cmd->av[1]);