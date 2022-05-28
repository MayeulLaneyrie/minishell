#ifndef BUILTINS_H
# define BUILTINS_H

/*
**	Dans builtin_central.c :
*/
int	builtin_search(char *s);
int	builtin_exec(t_sh *sh, t_cmd *cmd);
int	bi_exit(t_sh *sh, t_cmd *cmd);

/*
**	Dans env_builtin.c :
*/
int	bi_env(t_sh *sh, t_cmd *cmd);
int	bi_export(t_sh *sh, t_cmd *cmd);
int	bi_unset(t_sh *sh, t_cmd *cmd);

/*
**	Dans pwd_builtin.c :
*/
int	bi_pwd(t_sh *sh, t_cmd *cmd);

/*
**	Dans cd_builtin.c :
*/
int	bi_cd(t_sh *sh, t_cmd *cmd);

/*
**	Dans echo_builtin.c :
*/
int	bi_echo(t_sh *sh, t_cmd *cmd);

#endif
