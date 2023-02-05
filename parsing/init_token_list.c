/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 03:49:30 by ychun             #+#    #+#             */
/*   Updated: 2023/02/05 00:02:57 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_quote(char *cmd, int i, int type)
{
	if (type == T_SINGLE_QUOTES)
	{
		while (cmd[i] && cmd[i] != '\'')
		{
			if (cmd[i] == '\\' && cmd[i + 1] == '\'')
				i++;
			i++;
		}
	}
	else
	{
		while (cmd[i] && cmd[i] != '\"')
		{
			if (cmd[i] == '\\' && cmd[i + 1] == '\"')
				i++;
			i++;
		}
	}
	if (!cmd[i])
		return (-1);
	return (i);
}

int	find_quote_end(char *cmd, int i, t_token *token)
{
	if (!cmd[i + 1])
		return (-1);
	if (cmd[i] == '\'')
	{
		i++;
		i = find_quote(cmd, i, T_SINGLE_QUOTES);
		if (i == -1)
			return (-1);
		if (token)
			token->type = T_SINGLE_QUOTES;
	}
	else if (cmd[i] == '\"')
	{
		i++;
		i = find_quote(cmd, i, T_DOUBLE_QUOTES);
		if (i == -1)
			return (-1);
		if (token)
			token->type = T_DOUBLE_QUOTES;
	}
	return (i);
}

void	counting_token(char *cmd, int *count, int *i)
{
	while (cmd[*i])
	{
		if (cmd[*i] == ' ')
			(*i)++;
		else if (cmd[*i] == '\"' || cmd[*i] == '\'')
		{
			*i = find_quote_end(cmd, *i, NULL);
			if (*i == ERROR)
				break ;
			(*count)++;
			(*i)++;
		}
		else
		{
			while (cmd[*i] && cmd[*i] != ' ')
			{
				if (cmd[*i] == '\'' || cmd[*i] == '\"')
					break ;
				(*i)++;
			}
			(*count)++;
		}
	}
}

int	init_token_list(char *cmd, t_token_list *token_list)
{
	int	count_token;
	int	i;

	count_token = 0;
	i = 0;
	if (!cmd)
		return (ERROR);
	counting_token(cmd, &count_token, &i);
	if (i == ERROR)
		return (ERROR);
	token_list->count = count_token;
	token_list->token = (t_token *)malloc(sizeof(t_token) * (count_token + 1));
	if (!token_list->token)
		ft_error("Allocation Error", STDERR_FILENO);
	token_list->token = cmd_tokenizer(cmd, token_list->token,
			token_list->count);
	return (0);
}
