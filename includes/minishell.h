/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:36:25 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/16 17:31:28 by ychun            ###   ########.fr       */
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
# include <termios.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define STDIN 0
# define STDOUT 1

# define ERROR -1
# define SUCCESS 0

# define T_END 10
# define T_NULL 0
# define T_WORD 1
# define ARG 1
# define T_WORD_NULL 11
# define T_PIPE 2
# define INFILE_CHAR 30 // <
# define OUTFILE_CHAR 31 // >
# define HEREDOC_CHAR 32 // <<
# define OUTFILEOVER_CHAR 33 // >>
# define INFILE 40 // le mot apres <
# define OUTFILE 41 // le mot apres >
# define LIMITOR 42 // le mot apres <<
# define OUTFILEOVER 43 // le mot apres >>
# define T_SINGLE_QUOTES 5
# define T_DOUBLE_QUOTES 6

extern int					g_ret;

typedef struct s_cmd_line	t_cmd_line;

typedef struct s_token
{
	char	*word;
	int		type;
	char	*origin;
	int		flag_quotes_heredoc;
	int		flag_quotes;
	int		flag_env;
	int		tail;
}						t_token;

typedef struct s_token_list
{
	struct s_token	*token;
	int				count;
}	t_token_list;

struct s_cmd_line
{
	t_cmd_line		*begin;
	struct s_token	*token;
	t_cmd_line		*next;
	int				token_count;
	int				infile;
	int				outfile;
	char			**cmd_args;
};

typedef struct s_exec
{
	char	**cmd_paths;
	char	*cmd;
	int		pipe_nb;
	pid_t	pid;
	int		*pipe;
	int		id;
	int		flag;
	char	**envp;
}	t_exec;

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

/*****************Env********************/
void			env(char **cmd, t_env_list *env_list);
void			init_env_signal(char **env, t_env_list **env_list);
int				init_env(char *origin, char **key, char **value);
void			signal_handler(int signo);
char			*find_value_by_key(t_env_list *env_list,
					char *key, t_token **token);
t_env			*find_env_by_key(t_env_list *env_list, char *key);
void			get_new_env(t_env_list **env, char *key, char *value);
void			set_new_env(t_env_list **env_list, char *key, char *value);
void			ft_lstadd_back(t_env_list **new_env_list,
					t_env_list *tmp_env_list);
t_env_list		*ft_lstnew(t_env *new_env);
t_env			*ft_new_env(void);
int				ft_lstsize(t_env_list *list);
void			ft_error(char *str, int type);
int				ft_strcmp(const char *s1, const char *s2);
void			get_new_env_value(t_env *env, char *key, char *value);
void			ft_free_all_env(t_env_list *env_list);
void			update_env_value(t_env_list *env, char *key, char *value);

/*****************Token********************/
int				check_token_have_env(char *word);
int				find_tail_dollar(char *word, int i);
char			*ft_strjoin_word(char *word, char *value,
					char *head, char *tail);
char			*get_new_word(t_token **token, t_env_list *env,
					int head, int tail);
void			check_env_token(t_token_list *tokens, t_env_list *env);
t_token			*cmd_tokenizer(char *cmd, t_token *token, int count);
int				cmd_tokenizer_while(char *cmd, t_token *token,
					int *idx, int *i);
int				get_token_list(char *cmd_origin, t_env_list *env,
					t_token_list *token_list);
void			set_type_the_token(t_token_list *tokens);
int				init_token_list(char *cmd, t_token_list *token_list);
void			counting_token(char *cmd, int *count, int *i);
int				find_quote_end(char *cmd, int i, int *j, t_token *token);
int				find_quote(char *cmd, int i, int type, t_token *token);
void			ft_free_cmd_line(t_cmd_line *cmd_line);
int				syntax_check(t_token_list *token_list);
void			ft_free_token_list(t_token_list *tokens);
void			con_error_status(t_token_list *toknes, int status);
void			con_error_status2(t_token_list *toknes, int status);
void			init_tokens(t_token_list *tokens, int count);
t_token_list	*re_get_token_list(t_token_list *tokens, char *word, int idx);
void			token_copy(t_token *token, t_token *new_token,
					int idx, char **word);
void			get_new_dollar(t_token *token,
					int head_dollar, t_env_list *env);
int				check_space_beside_cmd(char *cmd, int j, int idx, int *i);
void			attach_after_word_quotes(t_token *token,
					int *i, int *idx, int status);
int				is_which_quote(char cmd);

/*****************Cmd_line********************/
t_cmd_line		*init_cmd_line(t_cmd_line *cmd_line_origin,
					t_token_list *tokens, int i);
int				count_token_before_pipe(t_token *token, int i);
t_cmd_line		*new_cmd_line(void);

/*****************Exec********************/
int				exec(t_cmd_line *cmd_line, t_env_list *env);
void			parent_free(t_exec *exec, t_cmd_line *line);
void			msg_error(char *str);
void			close_pipes(t_exec *exec, t_cmd_line *cmd_line);
void			child(t_exec exec, t_cmd_line *cmd_line, t_env_list *env);
int				create_pipes(t_exec *exec, t_cmd_line *cmd_line);
int				count_pipes(t_cmd_line *cmd_line);
void			here_doc(char *argv, t_cmd_line *cmd_line);
void			infile(char *word, t_cmd_line *cmd_line);
void			outfile(char *word, t_cmd_line *cmd_line);
void			outfileover(char *word, t_cmd_line *cmd_line);
void			get_files(t_exec *exec, t_cmd_line *cmd_line);
void			check_if_builtin(t_exec *exec, t_cmd_line *line,
					t_env_list *envp);
void			sub_dup(t_exec *exec, t_cmd_line *cmd_line);
void			last_cmd_dup(t_exec *exec, t_cmd_line *cmd_line);
char			**create_envp_char(t_env_list *env);
void			check_is_absolute_path(t_exec *exec, t_cmd_line *line,
					t_env_list *env);
int				get_flag(t_cmd_line *cmd_line);
void			put_right_message(t_exec *exec, t_cmd_line *cmd_line,
					t_env_list *env);
void			exec_exit_free_all(int ret, t_exec *exec, t_cmd_line *line,
					t_env_list *env);
void			set_ret(int status);

/*****************Builtin********************/

int				cd(char **cmd, t_env_list *env);
int				echo(char **cmd);
void			env(char **cmd, t_env_list *env_list);
void			export(char **cmd, t_env_list *env_list);
int				exit_cmd(char **cmd);
int				pwd(char **cmd);
void			unset(char **cmd, t_env_list *env_list);

#endif
