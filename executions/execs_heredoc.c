/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <aboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:14:06 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/20 12:12:28 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_heredoc(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
	}
}

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
	new_word = (char *)malloc(sizeof(char)
			* (ft_strlen(buf) - (tail - head) + ft_strlen(value) + 1));
	if (!new_word)
		ft_error("Allocation error", STDERR_FILENO);
	ft_strjoin_word(new_word, value, ft_substr(buf, 0, head),
		ft_substr(buf, tail + 1, ft_strlen(buf)));
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
	write(file, new_buf, ft_strlen(buf));
	write(file, "\n", 1);
}

void	here_doc(char *argv, t_cmd_line *cmd_line,
	t_env_list *env, int flag_quotes)
{
	int		file;
	char	*buf;

	signal(SIGINT, SIG_DFL);
	file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (file == -1)
		msg_error("FAILED TO CREATE HEREDOC\n");
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
		write_in_heredoc(file, buf, env, flag_quotes);
		free(buf);
	}
	free(buf);
	close(file);
	cmd_line->infile = open(".heredoc_tmp", O_RDONLY);
	if (cmd_line->infile == -1)
	{
		unlink(".heredoc_tmp");
		msg_error("FAILED TO OPEN HEREDOC");
	}
	signal(SIGINT, signal_handler);
}
