/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 03:45:25 by ychun             #+#    #+#             */
/*   Updated: 2023/02/13 20:09:08 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_type_red_word(t_token *token)
{
	int	i;

	i = -1;
	while (token[++i].type != T_NULL)
	{
		if (token[i].type >= 30 && token[i].type <= 33)
		{
			i++;
			if (token[i].type == T_NULL)
				return ;
			if (token[i].type == T_WORD)
			{
				if (token[i - 1].type == INFILE_CHAR)
					token[i].type = INFILE;
				else if (token[i - 1].type == OUTFILE_CHAR)
					token[i].type = OUTFILE;
				else if (token[i - 1].type == HEREDOC_CHAR)
					token[i].type = LIMITOR;
				else if (token[i - 1].type == OUTFILEOVER_CHAR)
					token[i].type = OUTFILEOVER;
			}
		}
	}
}

int	set_type_redirection(t_token_list *tokens, int i)
{
	if (!ft_strcmp(tokens->token[i].word, ">"))
		tokens->token[i].type = OUTFILE_CHAR;
	else if (!ft_strcmp(tokens->token[i].word, ">>"))
		tokens->token[i].type = OUTFILEOVER_CHAR;
	else if (!ft_strcmp(tokens->token[i].word, "<"))
		tokens->token[i].type = INFILE_CHAR;
	else if (!ft_strcmp(tokens->token[i].word, "<<"))
		tokens->token[i].type = HEREDOC_CHAR;
	return (i);
}

void	set_type_the_token(t_token_list *tokens)
{
	int	i;

	i = -1;
	while (tokens->token[++i].type != T_NULL)
	{
		if (!ft_strcmp(tokens->token[i].word, "|"))
			tokens->token[i].type = T_PIPE;
		else if (!ft_strcmp(tokens->token[i].word, ">")
			|| !ft_strcmp(tokens->token[i].word, ">>")
			|| !ft_strcmp(tokens->token[i].word, "<")
			|| !ft_strcmp(tokens->token[i].word, "<<"))
			i = set_type_redirection(tokens, i);
		else if (tokens->token[i].type != T_WORD_NULL)
			tokens->token[i].type = T_WORD;
	}
}

void	init_tokens(t_token_list *tokens, int count)
{
	int	i;

	i = -1;
	while (++i < count)
	{
		tokens->token[i].word = NULL;
		tokens->token[i].type = -1;
		tokens->token[i].origin = NULL;
		tokens->token[i].flag_quotes = 0;
		tokens->token[i].tail = 0;
		tokens->token[i].flag_env = 0;
	}
	tokens->token[i].word = NULL;
	tokens->token[i].type = -1;
	tokens->token[i].origin = NULL;
	tokens->token[i].flag_quotes = 0;
	tokens->token[i].tail = 1;
	tokens->token[i].flag_env = 0;
}

int	get_token_list(char *cmd_origin, t_env_list *env, t_token_list *token_list)
{
	if (init_token_list(cmd_origin, token_list))
		return (-2);
	check_env_token(token_list, env);
	set_type_the_token(token_list);
	set_type_red_word(token_list->token);
	if (syntax_check(token_list))
		return (ERROR);
	return (SUCCESS);
}
