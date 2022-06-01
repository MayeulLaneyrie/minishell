#include "../include/minishell.h"

int	apply_single_redir(t_red *red)
{
	int	flags;
	int	fd;

	if (!red || ! red->word)
		return (-1);
	flags = (red->in_out == RED_IN) * O_RDONLY
		| (red->in_out == RED_OUT) * (O_CREAT | O_WRONLY);
	if (red->in_out == RED_OUT)
		flags |= (red->mode == RED_TRUNC) * O_TRUNC
			| (red->mode == RED_APPEND) * O_APPEND;
	fd = open(red->word, flags, 0644);
	if (fd < 0)
		return (ft_err4("minishell", red->word, strerror(errno), NULL) - 1);
	red->fd = red->in_out == RED_OUT;
	if (dup2(fd, red->fd) < 0)
		return (-1);
	return (0);
}

int	apply_redir(t_cmd *cmd)
{
	t_list	*head;
	int		ret;

	ret = 0;
	head = cmd->red;
	while (head && !ret)
	{
		ret = apply_single_redir(head->data);
		head = head->next;
	}
	return (ret);
}
