# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pdrake <pdrake@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/12 16:09:06 by pdrake            #+#    #+#              #
#    Updated: 2021/01/12 16:09:08 by pdrake           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC 	= $(wildcard *.c)
OBJ 	= ${SRC:.c=.o}
LIBFT	= ./libft
MLX_PATH = ./minilibx_mms_20200219
MLX_FLAGS = -framework OpenGL -framework AppKit
MLX_LIB = mlxlib.a

NAME 	= miniRT

CC		= gcc
RM 		= rm -f

CFLAGS 	= -Wall -Wextra -Werror

.c.o:
				${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:		${OBJ}
		$(MAKE) -C $(LIBFT)/
		$(MAKE) -C $(MLX_PATH)/
		cp $(LIBFT)/libft.a ./$(NAME)
		gcc  -o ${NAME} ${OBJ} -L$(MLX_PATH) -lmlx

all:			${NAME}

debug: ${SRC}
	$(MAKE) -C $(LIBFT)
	$(CC) -Ilibft -Llibft -lft $(CFALGS) -g $(SRC) -o debug
clean:
				${RM} ${OBJ}

fclean:			clean
				${RM} ${NAME} miniRT

re:				fclean all

.PHONY =		cp all clean fclean re
.DEFAULT_GOAL =	all