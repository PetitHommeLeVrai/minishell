/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tokenizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:39:06 by ychun             #+#    #+#             */
/*   Updated: 2023/02/15 04:33:19 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#define BEFORE_WORD 100
#define AFTER_WORD 101
#define T_DO 6

void	cmd_tokenizer_while2(t_token *token, int **i, int **idx, int flag)
{
	char	*tmp;
	char	*tmp2;
	char	*ret;

	if (flag == BEFORE_WORD)
	{
		tmp = (token[**i]).word;
		tmp2 = (token[**i - 1]).word;
		ret = ft_strjoin(tmp2, tmp);
		free((token[**i]).word);
		free((token[**i - 1]).word);
		(**i)--;
		(token[(**i)]).word = ret;
		(token[(**i)]).flag_quotes_heredoc = 1;
		(**i)++;
		(**idx)++;
	}
	else
	{
		(**idx)++;
		(**i)++;
	}
}

void	cmd_tokenizer_while3(char *cmd, int **idx, int *j)
{
	*j = **idx;
	while (cmd[**idx] && cmd[**idx] != ' ')
	{
		if (cmd[**idx] == '\'' || cmd[**idx] == '\"'
			|| cmd[**idx] == '<' || cmd[**idx] == '>' || cmd[**idx] == '|')
			break ;
		(**idx)++;
	}
}

int	cmd_tokenizer_while(char *cmd, t_token *token, int *idx, int *i)
{
	int	j;
	int	flag;

	if (cmd[*idx] == '\'' || cmd[*idx] == '\"')
	{
		j = ++(*idx);
		*idx = find_quote_end(cmd, --(*idx), &j, &token[*i]);
		if (*idx == -1)
			return (-1);
		if (cmd[++j] == '\'' || cmd[j] == '\"')
			token[*i].word = ft_strdup("");
		else
			token[*i].word = ft_substr(cmd, j, *idx - j);
		flag = check_space_beside_cmd(cmd, j - 1, *idx, NULL);
		j = *idx;
		cmd_tokenizer_while2(token, &i, &idx, flag);
		return (j);
	}
	else if (cmd[*idx] != ' ' && cmd[*idx])
	{
		cmd_tokenizer_while3(cmd, &idx, &j);
		if (*idx - j > 0)
			token[(*i)++].word = ft_substr(cmd, j, *idx - j);
	}
	return (-1);
}

void	cmd_tokenizer_redirection(char *cmd, t_token *token, int *idx, int *i)
{
	if ((cmd[*idx + 1] == '<' && cmd[*idx] == '<') && cmd[*idx] != '|')
	{
		token[*i].word = ft_substr(cmd, *idx, 2);
		(*idx)++;
		(*i)++;
	}
	else if ((cmd[*idx + 1] == '>' && cmd[*idx] == '>') && cmd[*idx] != '|')
	{
		token[*i].word = ft_substr(cmd, *idx, 2);
		(*idx)++;
		(*i)++;
	}
	else
	{
		token[*i].word = ft_substr(cmd, *idx, 1);
		(*i)++;
	}
	(*idx)++;
}

t_token	*cmd_tokenizer(char *cmd, t_token *token, int count)
{
	int	i;
	int	j;
	int	idx;
	int	status;

	i = 0;
	idx = 0;
	while (cmd[idx] && i < count)
	{
		if (cmd[idx] == ' ')
			idx++;
		if (cmd[idx] == '<' || cmd[idx] == '>' || cmd[idx] == '|')
			cmd_tokenizer_redirection(cmd, token, &idx, &i);
		j = cmd_tokenizer_while(cmd, token, &idx, &i);
		if (i > 1 && token[i - 1].word && (token[i - 2].type == T_DO
				|| token[i - 2].type == T_SINGLE_QUOTES
				|| token[i - 2].flag_quotes_heredoc == 1))
		{
			status = check_space_beside_cmd(cmd, j, idx, &i);
			if (status == BEFORE_WORD)
				attach_after_word_quotes(token, &i, &idx, status);
		}
	}
	token[i].type = T_NULL;
	return (token);
}
