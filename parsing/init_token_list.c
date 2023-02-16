/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 03:49:30 by ychun             #+#    #+#             */
/*   Updated: 2023/02/16 17:29:48 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_quote(char *cmd, int i, int type, t_token *token)
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
	else if (type == T_DOUBLE_QUOTES)
	{
		while (cmd[i] && cmd[i] != '\"')
		{
			if (cmd[i] == '\\' && cmd[i + 1] == '\"')
				i++;
			i++;
		}
		if (token)
			token->flag_quotes = 1;
	}
	if (!cmd[i])
	{
		if (type == T_SINGLE_QUOTES)
			return (-1);
		return (-2);
	}
	return (i);
}

int	find_quote_end(char *cmd, int i, int *j, t_token *token)
{
	if (!cmd[i + 1])
		return (is_which_quote(cmd[i]));
	if (j != 0 && (cmd[*j - 1] == '\"' || cmd[*j - 1] == '\''))
		(*j)--;
	if (cmd[i] == '\'')
	{
		i = find_quote(cmd, i + 1, T_SINGLE_QUOTES, token);
		if (i < 0)
			return (i);
		if (token)
		{
			token->type = T_SINGLE_QUOTES;
			token->flag_quotes = 1;
		}
	}
	else if (cmd[i] == '\"')
	{
		i = find_quote(cmd, i + 1, T_DOUBLE_QUOTES, token);
		if (i < 0)
			return (i);
		if (token)
			token->type = T_DOUBLE_QUOTES;
	}
	return (i);
}

void	counting_token_2(char *cmd, int **count, int **i)
{
	if (cmd[**i] == '|')
	{
		(**count)++;
		if (**i != 0)
		{
			if (cmd[**i - 1] != ' ')
				(**count)++;
		}
		if (cmd[**i + 1] == ' ')
			(**i)++;
	}
	else if (cmd[**i] == '<' || cmd[**i] == '>')
	{
		if (cmd[**i + 1])
			(**i)++;
		(**count)++;
		if (**i != 0)
		{
			if (cmd[**i - 1] != ' ')
				(**count)++;
		}
		if ((cmd[**i] == '<' || cmd[**i] == '>') && cmd[**i + 1] == ' ')
			(**i)++;
	}
}

void	counting_token(char *cmd, int *count, int *i)
{
	if (cmd[*i] == ' ')
		(*i)++;
	while (cmd[(*i)])
	{
		if (cmd[*i] == '\"' || cmd[*i] == '\'')
		{
			*i = find_quote_end(cmd, *i, 0, NULL);
			if (*i < 0)
				break ;
			(*count)++;
			(*i)++;
		}
		while (cmd[*i] && cmd[*i] != ' ')
		{
			if (cmd[*i] == '\'' || cmd[*i] == '\"')
				break ;
			if (cmd[*i] == '<' || cmd[*i] == '>' || cmd[*i] == '|')
				counting_token_2(cmd, &count, &i);
			(*i)++;
		}
		if (cmd[*i] == ' ')
			(*i)++;
		if (cmd[*i - 1] != '<' || cmd[*i - 1] != '>' || cmd[*i - 1] != '|')
			(*count)++;
	}
}

int	init_token_list(char *cmd, t_token_list *token_list)
{
	int	count_token;
	int	i;

	count_token = 0;
	i = 0;
	counting_token(cmd, &count_token, &i);
	if (i < 0)
		return (i);
	token_list->count = count_token;
	token_list->token = (t_token *)malloc(sizeof(t_token) * (count_token + 1));
	if (!token_list->token)
		ft_error("Allocation Error", STDERR_FILENO);
	init_tokens(token_list, count_token);
	token_list->token = cmd_tokenizer(cmd, token_list->token,
			token_list->count);
	return (0);
}
