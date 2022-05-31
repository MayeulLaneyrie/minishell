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

// int	fill_struct_redir(t_sh *sh, char *s)
// {
// 	// t_list	*red;
// 	int		i;
// 	int		quote;
// 	int		d_quote;
// 	int		stck_i_err;

// 	i = 0;
// 	quote = 0;
// 	d_quote = 0;
// 	(void)sh;
// 	while (s[i])
// 	{
// 		in_out_quotes(s[i], &quote, &d_quote);
// 		if (quote == 0 && d_quote == 0 && (s[i] == '>' || s[i] == '<'))
// 		{
// 			if (check_after(s, i))
// 			{
// 				stck_i_err = i;
// 				// create_files(); create file before stck_i_err
// 				return (1);
// 			}
// 		}
// 		i++;
// 	}
// 	// stock;
// 	return (0);
// }
