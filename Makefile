# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ychun <ychun@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/14 12:33:27 by aboyer            #+#    #+#              #
#    Updated: 2023/01/25 02:07:46 by ychun            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADERS = -I includes -I libft

SRC =	main.c \
		env/init_env_signal.c \
		env/utile_env.c

OBJ = $(SRC:.c=.o)
NAME = minishell
CC = clang
FLAGS = -Wall -Wextra -Werror -g3
LD_FLAGS = -L libft
RM = rm -f

%.o: %.c 
			${CC} ${FLAGS} ${HEADERS} -c $< -o ${<:.c=.o}

all: ${NAME}
			
${NAME}: ${OBJ} 
			make -C libft
			${CC} ${FLAGS} ${LD_FLAGS} ${OBJ} -lft -lreadline -o ${NAME}
			
clean:
	make clean -C libft
	${RM} ${OBJ}

fclean: clean
	make fclean -C libft
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
