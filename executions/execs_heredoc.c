/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:14:06 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/22 05:51:38 by ychun            ###   ########.fr       */
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

void	loop(char *argv, int fd, t_env_list *env, int flag_quotes)
{
	char	*buf;

	while (1)
	{
		buf = readline("> ");
		if (buf)
		{
			if (!ft_strncmp(argv, buf, ft_strlen(argv) + 1))
			{
				free(buf);
				break ;
			}
			write_in_heredoc(fd, buf, env, flag_quotes);
		}
		else
		{
			ft_putstr_fd("here-document delimited by end-of-file\n'", 2);
			exit(1);
		}
		free(buf);
	}
	exit(0);
}

void	here_doc(char *argv, t_token *token,
		t_cmd_line *cmd_line, t_env_list **env)
{
	int	fd;
	int	status;

	(void)cmd_line;
	fd = open(token->word, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	g_global.pid = fork();
	signal(SIGINT, heredoc_handler);
	if (g_global.pid == 0)
		loop(argv, fd, *env, token->flag_quotes);
	else if (g_global.pid > 0)
	{
		waitpid(g_global.pid, &status, 0);
		if (WIFEXITED(status) == 0)
			g_global.ret = HEREDOC_ERROR;
		else
			g_global.ret = WEXITSTATUS(status);
	}
	signal(SIGINT, signal_handler);
	close(fd);
}

int	exec_heredoc(t_cmd_line *cmd_line_origin, t_env_list **env)
{
	int			i;
	int			j;
	t_cmd_line	*cmd_line;

	j = 0;
	cmd_line = cmd_line_origin;
	while (cmd_line)
	{
		i = -1;
		while (++i < cmd_line->token_count)
			exec_heredoc2(cmd_line, &i, env, &j);
		cmd_line = cmd_line->next;
		if (g_global.ret == HEREDOC_ERROR)
		{
			printf("%d", g_global.ret);
			g_global.ret = 130;
			return (HEREDOC_ERROR);
		}
	}
	return (0);
}
