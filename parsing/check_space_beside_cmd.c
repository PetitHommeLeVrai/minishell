/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_space_beside_cmd.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 01:54:27 by ychun             #+#    #+#             */
/*   Updated: 2023/02/17 22:47:31 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#define BEFORE_WORD 100
#define AFTER_WORD 101

int	check_word_have_pipe_red(t_token *token, int *i)
{
	if (!ft_strcmp(token[*i - 1].word, "|")
		|| !ft_strcmp(token[*i - 1].word, "<")
		|| !ft_strcmp(token[*i - 1].word, "<<")
		|| !ft_strcmp(token[*i - 1].word, ">")
		|| !ft_strcmp(token[*i - 1].word, ">>"))
		return (-1);
	return (0);
}

void	attach_after_word_quotes(t_token *token, int *i, int *idx, int flag)
{
	char	*tmp;
	char	*tmp2;
	char	*ret;

	if (flag == BEFORE_WORD && !check_word_have_pipe_red(token, i))
	{
		tmp = (token[*i]).word;
		tmp2 = (token[*i - 1]).word;
		if (!tmp || !tmp2)
			return ;
		ret = ft_strjoin(tmp2, tmp);
		free((token[*i]).word);
		free((token[*i - 1]).word);
		(*i)--;
		(token[(*i)]).word = ret;
		(token[(*i)]).flag_quotes_heredoc = 1;
		(*i)++;
	}
	else
	{
		(*idx)++;
		(*i)++;
	}
}

int	check_space_beside_cmd(char *cmd, int j, int idx, int *i)
{
	if (j == -1)
	{
		if (cmd[idx - 1] == '\'' || cmd[idx - 1] == '\"')
			return (BEFORE_WORD);
		if (cmd[idx] == '\'' || cmd[idx] == '\"')
			idx--;
		while (cmd[idx] != '\"' && cmd[idx] != '\'')
			idx--;
		if (cmd[idx + 1] != ' ')
		{
			*i -= 1;
			return (BEFORE_WORD);
		}
	}
	if (idx == -1 && cmd[j - 1] == '\"')
		return (BEFORE_WORD);
	if (j > 0 && cmd[j - 1] != ' ' && cmd[j - 1] != '|'
		&& cmd[j - 1] != '<' && cmd[j - 1] != '>')
		return (BEFORE_WORD);
	else
		return (-1);
}
