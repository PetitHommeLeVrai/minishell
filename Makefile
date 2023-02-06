# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ychun <ychun@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/14 12:33:27 by aboyer            #+#    #+#              #
#    Updated: 2023/02/06 00:32:04 by ychun            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADERS = -I includes -I libft

SRC =	main.c \
		env/init_env_signal.c \
		env/set_new_env.c \
		env/utile_env.c	\
		env/ft_error.c \
		env/ft_free_all_env.c \
		parsing/check_env_token.c \
		parsing/cmd_tokenizer.c \
		parsing/init_cmd_list.c \
		parsing/init_token_list.c \
		parsing/ft_free_all_tokens.c \
		parsing/syntax_check.c
		
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
