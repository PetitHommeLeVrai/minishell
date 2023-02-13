/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tokenizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:39:06 by ychun             #+#    #+#             */
/*   Updated: 2023/02/13 03:26:18 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_tokenizer_while2(char cmd, t_token *token, int **i, int **idx)
{
	char	*tmp;
	char	*tmp2;
	char	*ret;

	if (cmd != ' ' && **i != 0 && (token[**i - 1]).word != NULL)
	{
		tmp = (token[**i]).word;
		tmp2 = (token[**i - 1]).word;
		ret = ft_strjoin(tmp2, tmp);
		free((token[**i]).word);
		free((token[**i - 1]).word);
		(**i)--;
		(token[(**i)]).word = ret;
		(token[(**i)]).flag_quotes = 1;
		(**i)++;
		(**idx)++;
	}
	else
	{
		(**idx)++;
		(**i)++;
	}
}

void	cmd_tokenizer_while(char *cmd, t_token *token, int *idx, int *i)
{
	int	j;

	if (cmd[*idx] == '\'' || cmd[*idx] == '\"')
	{
		j = ++(*idx);
		*idx = find_quote_end(cmd, --(*idx), &token[*i]);
		if (*idx == -1)
			return ;
		token[*i].word = ft_substr(cmd, j, *idx - j);
		cmd_tokenizer_while2(cmd[j], token, &i, &idx);
		return ;
	}
	else if (cmd[*idx] != ' ' && cmd[*idx])
	{
		j = *idx;
		while (cmd[*idx] && cmd[*idx] != ' ')
		{
			if (cmd[*idx] == '\'' || cmd[*idx] == '\"'
				|| cmd[*idx] == '<' || cmd[*idx] == '>' || cmd[*idx] == '|')
				break ;
			(*idx)++;
		}
		if (*idx - j > 0)
			token[(*i)++].word = ft_substr(cmd, j, *idx - j);
	}
}

t_token	*cmd_tokenizer(char *cmd, t_token *token, int count)
{
	int	i;
	int	idx;

	i = 0;
	idx = 0;
	while (cmd[idx] && i < count)
	{
		if (cmd[idx] == ' ')
			idx++;
		if (cmd[idx] == '<' || cmd[idx] == '>' || cmd[idx] == '|')
		{
			if ((cmd[idx + 1] == '<' || cmd[idx + 1] == '>') && cmd[idx] != '|')
			{
				token[i++].word = ft_substr(cmd, idx, 2);
				idx++;
			}
			else
				token[i++].word = ft_substr(cmd, idx, 1);
			idx++;
		}
		cmd_tokenizer_while(cmd, token, &idx, &i);
	}
	token[i].type = T_NULL;
	return (token);
}
