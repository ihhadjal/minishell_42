# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/08 12:12:56 by ihhadjal          #+#    #+#              #
#    Updated: 2025/06/10 12:57:07 by ihhadjal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = code/main.c code/lexer/lexer.c code/lexer/lexer_helper.c code/utils/utils.c \
		code/parser/parser.c code/parser/parser_helper.c code/lexer/lexer_helper_2.c \
		code/exec/builtin.c code/exec/utils_builtin.c code/parser/parser_helper2.c \
		code/parser/error_handling.c code/exec/utils_builtin2.c code/exec/unset_builtin.c \
		code/expander/expander.c code/exec/utils_builtin3.c code/expander/utils_expander.c \
		code/exec/utils_builtin4.c code/expander/utils_expander2.c code/exec/export_builtin.c \
		code/parsarg_builtins/parsarg_builtins.c code/parsarg_builtins/parsarg_export.c \
		code/parsarg_builtins/parsarg_export2.c code/parsarg_builtins/parsarg_unset.c \
		code/exec/execution.c code/exec/external_commands.c code/exec/heredoc.c code/exec/pipe_utils.c \
		code/exec/pipes.c code/exec/redirections.c code/exec/signals.c code/exec/utils_exec.c \
		code/exec/utils_exec2.c
OBJS = ${SRCS:.c=.o}
NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -pthread
LDFLAGS = -lreadline
RM = rm -rf
LIBFT = ./resources/libft


all : ${NAME}

${NAME}: ${OBJS}
	${MAKE} -C ./resources/libft/
	${CC} ${CFLAGS} -o ${NAME} ${OBJS} ./resources/libft/libft.a ${LDFLAGS}

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

clean:
	${MAKE} clean -C ./resources/libft/
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME} ./resources/libft/libft.a

re: fclean all

.PHONY: all clean fclean re