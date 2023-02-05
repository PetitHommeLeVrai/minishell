/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tokenizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:39:06 by ychun             #+#    #+#             */
/*   Updated: 2023/02/05 02:33:53 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_tokenizer_while(char *cmd, t_token *token, int *idx, int *i)
{
	int	j;

	if (cmd[*idx] == ' ')
		(*idx)++;
	else if (cmd[*idx] == '\'' || cmd[*idx] == '\"')
	{
		j = *idx;
		*idx = find_quote_end(cmd, *idx, &token[*i]);
		if (*idx == -1)
			return ;
		token[*i].word = ft_substr(cmd, j, *idx - j);
		(*i)++;
		(*idx)++;
	}
	else
	{
		j = *idx;
		while (cmd[*idx] && cmd[*idx] != ' ')
		{
			if (cmd[*idx] == '\'' || cmd[*idx] == '\"')
				break ;
			(*idx)++;
		}
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
		cmd_tokenizer_while(cmd, token, &idx, &i);
	return (token);
}
