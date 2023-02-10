/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <aboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:07:32 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/08 11:30:53 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TMP_H
# define TMP_H

# include <fcntl.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

int		g_ret = 0;

typedef enum s_enum
{
	NON,
	ARG,
	INFILE_CHAR,
	OUTFILE_CHAR,
	HEREDOC_CHAR,
	OUTFILEOVER_CHAR,
	INFILE,
	OUTFILE,
	LIMITOR,
	OUTFILEOVER
}						t_enum;

typedef struct s_token
{
	char				*word;
	int					type;
	char				*origin;
}						t_token;

typedef struct s_token_list
{
	struct s_token		*token;
	int					count;
}						t_token_list;

typedef struct s_cmd_line
{
	char				*cmd;
	struct s_token_list	*token_list;
	struct cmd_line		*next;
	int					infile;
	int					outfile;
	char				**cmd_args;
	int					pipe_nb;
}						t_cmd_line;

typedef struct s_exec
{
	char				**cmd_paths;
	char				*cmd;
	pid_t				pid;
	int					*pipe;
	int					id;
	char				**envp;
}						t_exec;

typedef struct s_env
{
	char				*origin;
	char				*key;
	char				*value;
}						t_env;

typedef struct s_env_list
{
	struct s_env		*content;
	struct s_env_list	*next;
}						t_env_list;

void					parent_free(t_exec *exec, t_cmd_line *line);
void					msg_error(char *str);
void					close_pipes(t_exec *exec, t_cmd_line *cmd_line);
void					creat_pipes(t_exec *exec, t_cmd_line *cmd_line);
int						count_pipes(t_cmd_line *cmd_line);
void					here_doc(char *argv, t_cmd_line *cmd_line);
void					infile(char *word, t_cmd_line *cmd_line);
void					outfile(char *word, t_cmd_line *cmd_line);
void					outfileover(char *word, t_cmd_line *cmd_line);
void					get_files(t_exec *exec, t_cmd_line *cmd_line);
void					check_if_builtin(t_cmd_line *line, t_env_list *envp);
void					sub_dup(t_exec *exec, t_cmd_line *cmd_line);
char					**create_envp_char(t_env_list *env);

#endif
