/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tokenizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 03:49:30 by ychun             #+#    #+#             */
/*   Updated: 2023/01/30 04:21:07 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	find_quote_end(char *cmd, int *i, int type)
{
	if (!cmd[*i + 1])
		*i = -1;
	*i++;
	if (cmd[*i] == '\"')
	{
		while (cmd[*i] && cmd[*i] != '\"')
			*i++;
	}
	if (!cmd[*i])
		*i = -1;
}

int	counting_token(char *cmd)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == ' ')
			i++;
		else if (cmd[i] == '\"' || cmd[i] == '\'')
		{
			find_quote_end(cmd, &i, T_SINGLE_QUOTES);
			if (i == -1)
				return (ERROR);
		}
	}
}

int	cmd_tokenizer(char *cmd, t_token_info *token_info)
{
	int	count_token;

	if (!cmd)
		return (ERROR);
	count_token = counting_token(cmd);	
}