SRCS		=	src/main.c

OBJS		= ${SRCS:.c=.o}

NAME		= minishell
CC			= clang -Wall -Wextra -Werror
RM			= rm -f
AR			= ar rcs

${NAME}:	$(OBJS) libft.a
	${CC} ${OBJS} ./libft/libft.a -o ${NAME}

libft.a:
	${MAKE} -C ./libft

all:		${NAME}

bonus:		${NAME}

%.o:		%.c
	${CC} -c $< -o $@

clean:
	${MAKE} clean -C ./libft
	${RM} ${OBJS} ${TEST_OBJS}

fclean:		clean
	${MAKE} fclean -C ./libft
	${RM} ${NAME}

re:			fclean all

.PHONY:		all bonus clean fclean re
