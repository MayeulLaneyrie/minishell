SRCS =	src/main.c \
		src/newdel_cmd_sh.c \
		src/main_part1.c \
		src/main_part2.c \
		src/env.c \
		src/util_part1.c \
		src/ft_split_b.c \
		src/split_utils.c \
		src/builtin_central.c \
		src/display_utils.c

OBJS		= ${SRCS:.c=.o}

NAME		= minishell
CC			= clang -Wall -Wextra -Werror
RM			= rm -f
AR			= ar rcs

${NAME}:	$(OBJS) libft.a
	@ echo -n "\033[1mCompiling ${NAME}...\033[0m"
	@ ${CC} ${OBJS} ./libft/libft.a -o ${NAME} -lreadline && echo " [DONE]"

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
