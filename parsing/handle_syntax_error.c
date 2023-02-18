/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_syntax_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 10:34:30 by ychun             #+#    #+#             */
/*   Updated: 2023/02/18 12:07:31 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	handle_syntax_error(t_token *err, t_token *next, t_token *prev, int status)
{
	if ((err->type == T_PIPE && status != 1)
		&& ((!next || next->type != T_PIPE) || prev->word == NULL))
		return (ERR_SYNTAX_PIPE);
	if (!next && status != 1)
		return (ERR_SYNTAX_NEWLINE);
	if (status == 1)
	{
		next->type = ERR_AMBIGUOUS;
		return (ERR_AMBIGUOUS);
	}
	next->type = ERR_SYNTAX;
	return (ERR_SYNTAX);
}

void	con_error_status(t_token_list *token_list, int status)
{
	t_token	*token;

	token = token_list->head;
	if (status == ERR_SYNTAX_PIPE)
		printf ("syntax error near unexpected token `%s'\n", "|");
	else if (status == ERR_SYNTAX_NEWLINE)
		printf ("syntax error near unexpected token `%s'\n", "newline");
	else if (status == ERR_AMBIGUOUS)
	{
		while (token->type != ERR_AMBIGUOUS)
			token = token->next;
		printf("%s: ambiguous redirect\n", token->origin);
		g_global.ret = 1;
		ft_free_token_list2(token_list);
		return ;
	}
	else if (status == ERR_SYNTAX)
		con_error_status3(token_list, status);
	ft_free_token_list2(token_list);
}

void	con_error_status2(int status)
{
	if (status == -1)
	{
		printf ("unexpected EOF while looking for matching `%s'\n", "\'");
		printf ("syntax error: unexpected end of file\n");
	}
	if (status == -2)
	{
		printf ("unexpected EOF while looking for matching `%s'\n", "\"");
		printf ("syntax error: unexpected end of file\n");
	}
	g_global.ret = 2;
}

void	con_error_status3(t_token_list *tokens, int status)
{
	t_token	*tmp;

	tmp = tokens->head;
	while (tmp->type == status)
		tmp = tmp->next;
	printf ("syntax error near unexpected token `%s'\n", tmp->word);
	g_global.ret = 2;
}
