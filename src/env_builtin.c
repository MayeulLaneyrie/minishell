#include "../include/minishell.h"

int	bi_env(t_sh *sh, t_cmd *cmd)
{
	int	i;

	(void)cmd;
	i = -1;
	while (++i < sh->env->len)
		printf("%s\n", ((char **)sh->env->data)[i]);
	return (CMD_WAIT);
}
