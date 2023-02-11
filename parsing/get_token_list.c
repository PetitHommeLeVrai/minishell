/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 03:45:25 by ychun             #+#    #+#             */
/*   Updated: 2023/02/11 23:19:45 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	set_type_redirection(t_token_list *tokens, int i)
{
	if (!ft_strcmp(tokens->token[i].word, ">"))
	{
		tokens->token[i].type = OUTFILE_CHAR;
		tokens->token[++i].type = OUTFILE;
	}
	else if (!ft_strcmp(tokens->token[i].word, ">>"))
	{
		tokens->token[i].type = OUTFILEOVER_CHAR;
		tokens->token[++i].type = OUTFILEOVER;
	}
	else if (!ft_strcmp(tokens->token[i].word, "<"))
	{
		tokens->token[i].type = INFILE_CHAR;
		tokens->token[++i].type = INFILE;
	}
	else if (!ft_strcmp(tokens->token[i].word, "<<"))
	{
		tokens->token[i].type = HEREDOC_CHAR;
		tokens->token[++i].type = LIMITOR;
	}
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

int	get_token_list(char *cmd_origin, t_env_list *env, t_token_list *token_list)
{
	if (init_token_list(cmd_origin, token_list))
		return (ERROR);
	check_env_token(token_list, env);
	set_type_the_token(token_list);
	if (syntax_check(token_list))
		return (ERROR);
	return (SUCCESS);
}
