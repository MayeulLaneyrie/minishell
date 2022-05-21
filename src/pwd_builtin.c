#include "../include/minishell.h"

int	bi_pwd(t_sh *sh, t_cmd *cmd)
{
	char	*buff;
	int		size;

	size = GNL_BUFFER_SIZE;
	while (1)
	{
		buff = malloc(size);
		if (!buff)
			exit(EXIT_FAILURE);
		if (getcwd(buff, size))
			break ;
		free(buff);
		if (errno != ERANGE || size > 0x8000)
		{
			g_xt_stat = 1;
			ft_err4(sh->exec_name, cmd->av[0], strerror(errno),
					"(error retrieving current directory)\n");
			return (CMD_NOWAIT);
		}
		size *= 2;
	}
	printf("%s\n", buff);
	free(buff);
	g_xt_stat = 0;
	return (CMD_NOWAIT);
}
