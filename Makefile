# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/08 12:12:56 by ihhadjal          #+#    #+#              #
#    Updated: 2025/03/26 13:20:18 by ihhadjal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = code/main.c code/minishell.c
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