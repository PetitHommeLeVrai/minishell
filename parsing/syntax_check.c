/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 20:53:01 by ychun             #+#    #+#             */
/*   Updated: 2023/02/18 17:55:47 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

/*int	first_case(t_token *curr)
{
	if (curr->next)
		if ((curr->type >= 30 && curr->type <= 33)
			&& !(curr->next->type >= 40 && curr->next->type <= 43))
			return (-1);
	else
		if (curr->type == T_PIPE || (curr->type >= 30 && curr->type <= 33))
			return (-1);
}

int middle_case(t_token *curr)
{
	t_token	*prev;

	prev = curr;
	curr = curr->next;
	while (curr->next)
	{
		if (curr->type == T_PIPE && curr->next->type != T_PIPE)
		curr = curr->next;
	}
}

int	last_case(t_token *curr)
{
	if ((curr->type == T_PIPE && !curr->next)
		|| (curr->type >= 30 && curr->type <= 33 && !curr->next))
		return (-1);
}

int	syntax_copy(t_token *head)
{
	t_token *curr;
	t_token *prev;

	curr = head;
	while (curr)
	{
		first_case(curr);
		if (curr->next)
			middle_case(curr);
		curr = curr->next;
		last_case(curr);
	}
}

int	syntax_check(t_token *head)
{
	t_token	*curr;
	t_token	*prev;

	curr = head;
	prev = NULL;
	ft_token_add_back(&curr, ft_new_token());
	while (curr)
	{
		if (curr->type == T_PIPE && (prev == NULL
				|| curr->next->type == -1 || curr->next->type == T_PIPE
				|| (curr->next->type >= 30 && curr->next->type <= 33
					&& prev->type != T_WORD)))
			return (handle_syntax_error(curr, curr->next, prev, 0));
		if ((curr->type >= 30 && curr->type <= 33) && (curr->next->type == -1
				|| (curr->next->type != T_WORD_NULL
				|| !(curr->next->type >= 40 && curr->next->type <= 43))))
			return (handle_syntax_error(curr, curr->next, prev, 0));
		if ((curr->type >= 30 && curr->type <= 33)
			&& (curr->next->word && curr->next->type == T_WORD_NULL))
			return (handle_syntax_error(curr, curr->next, prev, 1));
		prev = curr;
		curr = curr->next;
	}
	return (SUCCESS);
}
*/