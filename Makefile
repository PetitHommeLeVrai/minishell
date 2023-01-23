# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aboyer <aboyer@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/14 12:33:27 by aboyer            #+#    #+#              #
#    Updated: 2023/01/23 14:12:48 by aboyer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADERS = ./includes
SRC = main.c
OBJ = $(SRC:.c=.o)
NAME = minishell
CC = clang
FLAGS = -Wall -Wextra -Werror
RM = rm -f

%.o: %.c 
			${CC} ${FLAGS} -c $< -o $@ -I ${HEADERS} -g3

all: ${NAME}
			
${NAME}: ${OBJ} 
			${CC} ${FLAGS} ${OBJ} -o ${NAME} -g3
			
clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
