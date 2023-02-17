/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 20:53:01 by ychun             #+#    #+#             */
/*   Updated: 2023/02/17 22:54:24 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#define ERR_SYNTAX -200
#define ERR_SYNTAX_PIPE -201
#define ERR_SYNTAX_NEWLINE -202
#define ERR_AMBIGUOUS -203

int	find_quote_return(int type)
{
	if (type == T_SINGLE_QUOTES)
		return (-1);
	return (-2);
}

int	is_which_quote(char cmd)
{
	if (cmd == '\'')
		return (-1);
	else if (cmd == '\"')
		return (-2);
	else
		return (ERR_SYNTAX_NEWLINE);
}

void	con_error_status2(t_token_list *tokens, int status)
{
	int	i;

	i = 0;
	if (status == ERR_SYNTAX)
	{
		while (tokens->token[i].type == ERR_SYNTAX)
			i++;
		printf ("bash: syntax error near unexpected token `%s'\n",
			tokens->token[i].word);
	}
	if (status == -1)
	{
		printf ("bash: unexpected EOF while looking for matching `%s'\n", "\'");
		printf ("bash: syntax error: unexpected end of file\n");
	}
	if (status == -2)
	{
		printf ("bash: unexpected EOF while looking for matching `%s'\n", "\"");
		printf ("bash: syntax error: unexpected end of file\n");
	}
}

int	handle_syntax_error(t_token *err, t_token *next, t_token prev, int status)
{
	if ((err->type == T_PIPE && status != 1)
		&& ((next->type != T_NULL
				&& next->type != T_PIPE) || prev.word == NULL))
		return (ERR_SYNTAX_PIPE);
	if (next->type == T_NULL && status != 1)
		return (ERR_SYNTAX_NEWLINE);
	if (status == 1)
	{
		next->type = ERR_AMBIGUOUS;
		return (ERR_AMBIGUOUS);
	}
	next->type = ERR_SYNTAX;
	return (ERR_SYNTAX);
}

int	syntax_check(t_token_list *token_list)
{
	int		i;
	t_token	*tk;
	t_token	prev;

	tk = token_list->token;
	prev.word = NULL;
	i = -1;
	while (tk[++i].type != T_NULL)
	{
		if (tk[i].type == T_PIPE && (prev.word == NULL
				|| tk[i + 1].type == T_NULL || tk[i + 1].type == T_PIPE
				|| ((tk[i + 1].type >= 30 && tk[i].type <= 33
						&& prev.type != T_WORD))))
			return (handle_syntax_error(&tk[i], &tk[i + 1], prev, 0));
		if ((tk[i].type >= 30 && tk[i].type <= 33)
			&& (tk[i + 1].type == T_NULL
				|| (tk[i + 1].type >= 40 || tk[i + 1].type <= 43)))
			return (handle_syntax_error(&tk[i], &tk[i + 1], prev, 0));
		if ((tk[i].type >= 30 && tk[i].type <= 33)
			&& (tk[i + 1].type != T_NULL && tk[i + 1].type == T_WORD_NULL))
			return (handle_syntax_error(&tk[i], &tk[i + 1], prev, 1));
		prev = tk[i];
	}
	return (SUCCESS);
}
