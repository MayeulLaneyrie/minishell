# MkI :

- [x] Display a prompt and ask for a command line
- [x] Manage unquoted, simple and double quoted strings
- [x] Find and launch the correct executable, passing the correct arguments
- [x] Wait for the job to end, and store its exit status

- [x] "exit" builtin

* No history
* No expansion
* No redirection
* No pipes
* No handling of ctrl-c, ctrl-d, ctrl-\

> At that point, a command line should be made of only a simple command without any redirection.

# MkII :

* All MkI functionalities, plus the following :

- [x] Manage history
- [x] Manage pipes

* No expansion
* No redirection
* No handling of ctrl-c, ctrl-d, ctrl-\

# MkIII :

* All MkII functionalities, plus the following :

- [x] '<', '>' and '>>' redirections
- [x] Variable expansion

- [x] "env" builtin
- [x] "unset" builtin
- [x] "export" builtin

* No heredoc implementation
* No handling of ctrl-c, ctrl-d, ctrl-\

# MkIV :

* All MkIII functionalities, plus the following :

- [x] Handling of ctrl-c, ctrl-d, ctrl-\
- [x] Handling of $? expansion
- [x] Heredoc implementation
- [x] "echo" builtin
- [x] "cd" builtin
- [x] "pwd" builtin

> At that point, all the functionalities of the mandatory part should be implemented properly.

# MkV :	(BONUS)

* All MkIV functionalities plus the following :

- [ ] Manage && and || operators with parenthesis for priorities
- [ ] Perform '\*' file expansion for current directory

# Leaks :
echo coucou | wc -c
==27446== Open file descriptor 2: /dev/pts/1
==27446==    at 0x49BE8CB: dup2 (syscall-template.S:78)
==27446==    by 0x405517: builtin_exec (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x4034DA: cmd_proc (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x4037F7: spawn_pipe_cmd (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x4039B9: pipeline_spawner (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x403602: main_part2 (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x401570: main (in /home/bifrah/42/minishell/minishell)
==27446== 
==27446== Open file descriptor 1:
==27446==    at 0x49BE8CB: dup2 (syscall-template.S:78)
==27446==    by 0x405517: builtin_exec (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x4034DA: cmd_proc (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x4037F7: spawn_pipe_cmd (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x4039B9: pipeline_spawner (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x403602: main_part2 (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x401570: main (in /home/bifrah/42/minishell/minishell)
==27446== 
==27446== Open file descriptor 0: /dev/pts/1
==27446==    at 0x49BE8CB: dup2 (syscall-template.S:78)
==27446==    by 0x405517: builtin_exec (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x4034DA: cmd_proc (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x4037F7: spawn_pipe_cmd (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x4039B9: pipeline_spawner (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x403602: main_part2 (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x401570: main (in /home/bifrah/42/minishell/minishell)
==27446== 
==27446== 
==27446== 16 bytes in 1 blocks are still reachable in loss record 9 of 70
==27446==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==27446==    by 0x404024: new_split (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x403C1B: load_env (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x401862: new_sh (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x4014F3: main (in /home/bifrah/42/minishell/minishell)
==27446== 
==27446== 16 bytes in 1 blocks are still reachable in loss record 11 of 70
==27446==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==27446==    by 0x404024: new_split (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x401C87: parse_cmd (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x401FEA: main_part1 (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x401537: main (in /home/bifrah/42/minishell/minishell)
==27446== 
==27446== 18 bytes in 4 blocks are still reachable in loss record 12 of 70
==27446==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==27446==    by 0x40199C: no_redirect (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x401B98: cut_words (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x401D18: parse_cmd (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x401FEA: main_part1 (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x401537: main (in /home/bifrah/42/minishell/minishell)
==27446== 
==27446== 24 bytes in 1 blocks are still reachable in loss record 16 of 70
==27446==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==27446==    by 0x404055: new_split (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x401C87: parse_cmd (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x401FEA: main_part1 (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x401537: main (in /home/bifrah/42/minishell/minishell)
==27446== 
==27446== 30 bytes in 1 blocks are still reachable in loss record 18 of 70
==27446==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==27446==    by 0x4079DA: ft_strdup (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x40576E: export_single (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x403E72: set_var (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x4018BE: new_sh (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x4014F3: main (in /home/bifrah/42/minishell/minishell)
==27446== 
==27446== 48 bytes in 2 blocks are still reachable in loss record 22 of 70
==27446==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==27446==    by 0x404055: new_split (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x4041C8: list_to_split (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x401BD3: cut_words (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x401D18: parse_cmd (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x401FEA: main_part1 (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x401537: main (in /home/bifrah/42/minishell/minishell)
==27446== 
==27446== 128 bytes in 2 blocks are still reachable in loss record 27 of 70
==27446==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==27446==    by 0x401681: new_cmd (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x401CB1: parse_cmd (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x401FEA: main_part1 (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x401537: main (in /home/bifrah/42/minishell/minishell)
==27446== 
==27446== 640 bytes in 1 blocks are still reachable in loss record 33 of 70
==27446==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==27446==    by 0x404055: new_split (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x403C1B: load_env (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x401862: new_sh (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x4014F3: main (in /home/bifrah/42/minishell/minishell)
==27446== 
==27446== 4,240 bytes in 78 blocks are still reachable in loss record 56 of 70
==27446==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==27446==    by 0x4079DA: ft_strdup (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x403C65: load_env (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x401862: new_sh (in /home/bifrah/42/minishell/minishell)
==27446==    by 0x4014F3: main (in /home/bifrah/42/minishell/minishell)
==27446== 
7

sans compter les leaks de FD (envie de pleurer)