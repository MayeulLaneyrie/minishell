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
