/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <aboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:14:06 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/20 18:38:37 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_new_dollar_str(char *buf, t_env_list *env, int head, int tail)
{
	char	*key;
	char	*value;
	char	*new_word;

	key = ft_substr(buf, head + 1, tail - head);
	value = find_value_by_key(env, key, NULL);
	if (!ft_strcmp(key, "?"))
	{
		free(value);
		value = ft_itoa(g_global.ret);
	}
	new_word = (char *)malloc(sizeof(char) * (ft_strlen(buf) - (tail - head)
				+ ft_strlen(value) + 1));
	if (!new_word)
		ft_error("Allocation error", STDERR_FILENO);
	ft_strjoin_word(new_word, value, ft_substr(buf, 0, head), ft_substr(buf,
				tail + 1, ft_strlen(buf)));
	free(key);
	free(value);
	free(buf);
	return (new_word);
}

void	write_in_heredoc(int file, char *buf, t_env_list *env, int flag_quotes)
{
	int		count_dollar;
	int		head_dollar;
	int		tail_dollar;
	char	*new_buf;

	count_dollar = check_count_dollar(buf);
	new_buf = buf;
	while (count_dollar-- > 0 && flag_quotes != 1)
	{
		head_dollar = check_token_have_env(new_buf);
		tail_dollar = find_tail_dollar(new_buf, head_dollar + 1);
		new_buf = get_new_dollar_str(new_buf, env, head_dollar, tail_dollar);
	}
	write(file, new_buf, ft_strlen(new_buf));
	write(file, "\n", 1);
}

void	loop(char *argv, t_cmd_line *cmd_line, t_env_list *env, t_exec *exec)
{
	char	*buf;

	while (1)
	{
		buf = readline("> ");
		if (!buf)
		{
			printf("\n");
			break ;
		}
		if (!ft_strncmp(argv, buf, ft_strlen(argv) + 1))
			break ;
		write_in_heredoc(cmd_line->infile, buf, env, exec->flag_quotes);
	}
	free(buf);
}

void	here_doc(char *argv, t_exec *exec, t_cmd_line *cmd_line,
		t_env_list *env)
{

	signal(SIGINT, SIG_DFL);
	cmd_line->infile = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (cmd_line->infile == -1)
	{
		perror("heredoc");
		exec_exit_free_all(2, exec, cmd_line->begin, &env);
	}
	loop(argv, cmd_line, env, exec);
	close(cmd_line->infile);
	cmd_line->infile = open(".heredoc_tmp", O_RDONLY);
	if (cmd_line->infile == -1)
	{
		unlink(".heredoc_tmp");
		perror("heredoc");
		exec_exit_free_all(2, exec, cmd_line->begin, &env);
	}
	signal(SIGINT, signal_handler);
}
