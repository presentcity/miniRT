# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pdrake <pdrake@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/09 20:03:10 by presentcity       #+#    #+#              #
#    Updated: 2020/11/10 14:07:19 by pdrake           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = $(wildcard *.c)
DEP = libft.h
OBJ = ${SRC:.c=.o}

NAME = libft.a

CC = cc
RM = rm -f

CFLAGS = -Wall -Wextra -Werror

.c.o:
				${CC} ${CFLAGS} -c $< -include ${DEP} -o ${<:.c=.o}

${NAME}:		${OBJ}
				ar rc  ${NAME} ${OBJ} && ranlib ${NAME}

all:			${NAME}

clean:
				${RM} ${OBJ}

fclean:			clean
				${RM} ${NAME}

re:				fclean all

.PHONY =		all clean fclean re
.DEFAULT_GOAL =	all