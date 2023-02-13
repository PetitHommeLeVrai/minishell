# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ychun <ychun@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/14 12:33:27 by aboyer            #+#    #+#              #
#    Updated: 2023/02/13 21:34:58 by ychun            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADERS = -I includes -I libft

SRC =	main.c \
		env/init_env_signal.c \
		env/set_new_env.c \
		env/utile_env.c	\
		env/ft_error.c \
		env/ft_free_all_env.c \
		env/update_env_value.c \
		parsing/check_env_token.c \
		parsing/cmd_tokenizer.c \
		parsing/get_token_list.c \
		parsing/init_token_list.c \
		parsing/ft_free_cmd_line.c \
		parsing/syntax_check.c \
		parsing/init_cmd_line.c \
		parsing/re_get_token_list.c \
		executions/execs_child.c \
		executions/execs_files.c \
		executions/execs_heredoc.c \
		executions/execs_main.c \
		executions/execs_sub_dup.c \
		executions/execs_utils.c \
		builtins/cd.c \
		builtins/echo.c \
		builtins/env.c \
		builtins/exit.c \
		builtins/export.c \
		builtins/pwd.c \
		builtins/unset.c
		
OBJ = $(SRC:.c=.o)
NAME = minishell
CC = gcc
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
