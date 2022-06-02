SRCS =	src/main.c \
		src/newdel_cmd_sh.c \
		src/parser.c \
		src/redirect.c \
		src/dollar_subst.c \
		src/utils.c \
		src/cmd_launcher.c \
		src/pipe_stuff.c \
		src/search_path.c \
		src/env.c \
		src/split_utils.c \
		src/split_utils2.c \
		src/quote_split.c \
		src/display_utils.c \
		src/heredoc.c \
		src/apply_redir.c \
		src/bi_central.c \
		src/bi_env.c \
		src/bi_pwd.c \
		src/bi_cd.c \
		src/bi_echo.c \
		src/make_canonical.c \
		src/gnl.c

OBJS		= ${SRCS:.c=.o}

NAME		= minishell
CC			= clang -Wall -Wextra -Werror
ASAN		= -g -fsanitize=address
RM			= rm -f
AR			= ar rcs

${NAME}:	$(OBJS) libft.a
	@ echo -n "\033[1mCompiling ${NAME}...\033[0m"
	@ ${CC} ${ASAN} ${OBJS} ./libft/libft.a -o ${NAME} -lreadline && echo " [DONE]"

libft.a:
	@ echo -n "\033[1mMaking libft...\033[0m"
	@ ${MAKE} --no-print-directory -C ./libft && echo " [DONE]"

all:		${NAME}

bonus:		${NAME}

%.o:		%.c
	@ echo -n "\033[1mBuilding objects...\033[0m"
	@ ${CC} -c $< -o $@ && echo " [DONE]"

clean:
	@ echo -n "\033[1mCleaning libft...\033[0m"
	@ ${MAKE} --no-print-directory clean -C ./libft && echo " [DONE]"
	@ echo -n "\033[1mCleaning object files...\033[0m"
	@ ${RM} ${OBJS} ${TEST_OBJS} && echo " [DONE]"

fclean:		clean
	@ echo -n "\033[1mCleaning binaries...\033[0m"
	@ ${RM} ./libft/libft.a
	@ ${RM} ${NAME}
	@ echo " [DONE]"

re:			fclean all

.PHONY:		all bonus clean fclean re
