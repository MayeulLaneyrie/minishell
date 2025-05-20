SRCS =	src/main.c \
		src/newdel_cmd_sh.c \
		src/parser.c \
		src/parser2.c \
		src/wrd_len_and_cpy.c \
		src/dollar_subst.c \
		src/check_utils.c \
		src/check1.c \
		src/check2.c \
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
		src/gnl.c \
		src/signal_handler.c

OBJS		= ${SRCS:.c=.o}

NAME		= minishell
CC			= gcc -Wall -Wextra -Werror -g3
ASAN		= -g -fsanitize=address
RM			= rm -f
AR			= ar rcs

${NAME}:	$(OBJS) libft.a
	@ echo -en "\e[1mCompiling ${NAME}...\e[0m"
	@ ${CC} ${OBJS} ./libft/libft.a -o ${NAME} -lreadline && echo " [DONE]"

libft.a:
	@ echo -en "\e[1mMaking libft...\e[0m"
	@ ${MAKE} --no-print-directory -C ./libft && echo " [DONE]"

all:		${NAME}

bonus:		${NAME}

%.o:		%.c
	@ echo -en "\e[1mBuilding object $@...\e[0m"
	@ ${CC} -c $< -o $@ && echo " [DONE]"

clean:
	@ echo -en "\e[1mCleaning libft...\e[0m"
	@ ${MAKE} --no-print-directory clean -C ./libft && echo " [DONE]"
	@ echo -en "\e[1mCleaning object files...\e[0m"
	@ ${RM} ${OBJS} ${TEST_OBJS} && echo " [DONE]"

fclean:		clean
	@ echo -en "\e[1mCleaning binaries...\e[0m"
	@ ${RM} ./libft/libft.a
	@ ${RM} ${NAME}
	@ echo " [DONE]"

re:			fclean all

.PHONY:		all bonus clean fclean re
