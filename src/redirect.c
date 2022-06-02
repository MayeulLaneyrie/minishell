#include "../include/minishell.h"

void	in_out_quotes(char c, int *quote, int *d_quote)
{
	if (c == '"' && !*quote && !*d_quote)
		*d_quote = 1;
	else if (c == '"' && *d_quote)
		*d_quote = 0;
	else if (c == '\'' && !*quote && !*d_quote)
		*quote = 1;
	else if (c == '\'' && *quote)
		*quote = 0;
}
