/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 03:45:25 by ychun             #+#    #+#             */
/*   Updated: 2023/02/20 16:20:59 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_type_red_word(t_token *token)
{
	while (token)
	{
		if (!token->next)
			return ;
		if (token->type >= 30 && token->type <= 33)
		{
			if (token->next->type == T_WORD)
			{
				if (token->type == INFILE_CHAR)
					token->next->type = INFILE;
				else if (token->type == OUTFILE_CHAR)
					token->next->type = OUTFILE;
				else if (token->type == HEREDOC_CHAR)
					token->next->type = LIMITOR;
				else if (token->type == OUTFILEOVER_CHAR)
					token->next->type = OUTFILEOVER;
			}
		}
		token = token->next;
	}
}

int	get_token_list(char *cmd_origin, t_env_list *env, t_token_list *token_list)
{
	int		syntax_error;
	t_token	*tmp;
	int		count_dollar;

	token_list->head = NULL;
	token_list->tail = NULL;
	token_list->count = 0;
	count_dollar = 0;
	cmd_tokenizer(cmd_origin, token_list);
	check_env_token(token_list, env, count_dollar);
	remove_space_token(token_list->head);
	set_type_red_word(token_list->head);
	tmp = token_list->head;
	while (tmp)
	{
		if (tmp->type == T_SINGLE_QUOTES || tmp->type == T_DOUBLE_QUOTES)
			tmp->type = T_WORD;
		tmp = tmp->next;
	}
	syntax_error = syntax_check(token_list->head);
	if (syntax_error < 0)
		return (syntax_error);
	return (SUCCESS);
}
