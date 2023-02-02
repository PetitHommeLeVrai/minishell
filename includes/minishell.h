/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:36:25 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/02 19:52:50 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <error.h>
# include <string.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define STDIN 0
# define STDOUT 1

# define ERROR -1
# define SUCCESS 1

# define T_NULL 0
# define T_WORD 1
# define T_PIPE 2
# define T_REDIRECTION 30
# define T_RED_R 31
# define T_RED_RR 32
# define T_RED_L 33
# define T_RED_LL 34
# define T_SINGLE_QUOTES 5
# define T_DOUBLE_QUOTES 6

typedef struct s_token
{
	char				*word;
	int					type;
	struct s_token		*next;
}						t_token;

typedef struct s_token_list
{
	struct s_token	*token;
	int				count;
}	t_token_list;

typedef struct s_cmd_line
{
	char				*cmd;
	struct s_token		*word;
	struct cmd_line		*next;
}						t_cmd_line;

typedef struct s_env
{
	char	*origin;
	char	*key;
	char	*value;
}	t_env;

typedef struct s_env_list
{
	struct s_env		*content;
	struct s_env_list	*next;
}	t_env_list;

#endif