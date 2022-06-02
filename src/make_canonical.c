#include "../include/minishell.h"

int	jump_noslash(char *s, int gap)
{
	int	i;

	i = 0;
	while (s[i + gap] && s[i + gap] != '/')
	{
		s[i] = s[i + gap];
		if (gap)
			s[i + gap] = 0;
		i++;
	}
	return (i);
}

int	remove_dot(char *s)
{
	int	gap;

	gap = 0;
	while (s[gap])
	{
		while (s[gap] && s[gap] == '/')
		{
			*s = s[gap];
			s++;
		}
		if (s[gap] == '.' && (s[gap + 1] == '/' || !s[gap + 1]))
			gap += 2;
		else
			s += jump_noslash(s, gap);
	}
	*s = '\0';
	return (0);
}

int	cancel_dotdot(char *s, int n)
{
	int	ret;
	int	i;

	ret = 0;
	i = n;
	while (i && s[--i] == '/')
		ret++;
	if (!i && s[0] == '/')
		return (ret - 1);
	if (!i)
		return (0);
	while (i && s[i--] != '/')
		ret++;
	return (ret);
}

int	remove_dotdot(char *s)
{
	int	i;
	int	gap;

	i = 0;
	gap = 0;
	while (s[i + gap])
	{
		while (s[i + gap] && s[i + gap] == '/')
		{
			s[i] = s[i + gap];
			i++;
		}
		if (s[i + gap] == '.' && s[i + gap + 1] == '.'
			&& (s[i + gap + 2] == '/' || !s[i + gap + 2]))
		{
			gap += 2 + (s[i + gap + 2] == '/') + cancel_dotdot(s, i);
			i -= cancel_dotdot(s, i);
			while (s[i + gap] && s [i + gap] == '/')
				gap++;
		}
		else
			i += jump_noslash(s + i, gap);
	}
	return (s[i] = 0);
}

int	make_canonical(char *s)
{
	int	i;
	int	gap;

	remove_dot(s);
	remove_dotdot(s);
	gap = 0;
	i = 0;
	while (s[i + gap])
	{
		i += jump_noslash(s + i, gap);
		if (!s[i + gap])
			break ;
		i++;
		while (s[i + gap] && s[i + gap] == '/')
			gap++;
	}
	s[i] = '\0';
	return (s[0]);
}
