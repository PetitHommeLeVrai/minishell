/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:36:25 by aboyer            #+#    #+#             */
/*   Updated: 2023/01/24 00:32:09 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define STDIN 0
# define STDOUT 1

# define ERROR -1
# define SUCCESS 1

typedef struct s_cmd
{
	char			**cmd_paths;
	char			**cmd_argv;
	int				pipe[2];
	int				infile;
	int				outfile;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_cmd_list
{
	struct s_cmd	*cmd_list;
	struct s_cmd	*cmd_list_tail;
}	t_cmd_list;


#endif