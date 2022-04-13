#include "../include/minishell.h"

char	*ft_cat3(char *s1, char *s2, char *s3)
{
	char	*ret;
	int		size;

	size = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1;
	ret = malloc(size);
	if (!ret)
		return (NULL);
	*ret = 0;
	ft_strlcat(ret, s1, size);
	ft_strlcat(ret, s2, size);
	ft_strlcat(ret, s3, size);
	return (ret);
}

char	*ft_catn(int n, char **s, char *sep)
{
	char	*ret;
	int		size;
	int		i;

	size = ft_strlen(sep) * n + 1;
	i = -1;
	while (++i < n)
		size += ft_strlen(s[i]);
	ret = malloc(size);
	if (!ret)
		return (NULL);
	i = -1;
	*ret = 0;
	while (++i < n)
	{
		ft_strlcat(ret, s[i], size);
		if (i != n - 1)
			ft_strlcat(ret, sep, size);
	}
	return (ret);
}

int	ft_err4(char *s1, char *s2, char *s3, char *s4)
{
	char	*s[4];
	char	*display;

	s[0] = s1;
	s[1] = s2;
	s[2] = s3;
	s[3] = s4;
	display = ft_catn((s1 != 0) + (s2 != 0) + (s3 != 0) + (s4 != 0), s, ": ");
	if (!display)
		return (-1);
	write(2, display, ft_strlen(display));
	free(display);
	return (0);
}