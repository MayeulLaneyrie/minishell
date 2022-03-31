#ifndef ENV_H
# define ENV_H

/*
**	This one is pretty self explanatory. Please note that the return value is
**	not copied. It means that you don't have to free it, but also that you may
**	want to copy it yourself for long-term use, as subsequent calls to set_var
**	and unset_var may change the pointed data.
*/
char	*get_var(char **envp, char *name);

#endif
