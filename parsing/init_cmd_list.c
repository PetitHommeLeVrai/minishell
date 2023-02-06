/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 03:45:25 by ychun             #+#    #+#             */
/*   Updated: 2023/02/06 01:41:22 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_type_the_token(t_token_list *tokens)
{
	int	i;

	i = -1;
	tokens->token[tokens->count].type = T_NULL;
	while (tokens->count > ++i)
	{
		if (!ft_strcmp(tokens->token[i].word, "|"))
			tokens->token[i].type = T_PIPE;
		else if (!ft_strcmp(tokens->token[i].word, ">")
			|| !ft_strcmp(tokens->token[i].word, ">>"))
			tokens->token[i].type = T_REDIRECTION;
		else if (!ft_strcmp(tokens->token[i].word, "<")
			|| !ft_strcmp(tokens->token[i].word, "<<"))
			tokens->token[i].type = T_REDIRECTION;
		else if (tokens->token[i].type != T_WORD_NULL)
			tokens->token[i].type = T_WORD;
	}
}

t_cmd_line	*init_cmd_line(char *cmd_origin, t_env_list *env)
{
	t_cmd_line		*cmd_line;
	t_token_list	token_list;

	cmd_line = NULL;
	token_list.token = NULL;
	token_list.count = 0;
	if (!cmd_origin)
		return (NULL);
	if (init_token_list(cmd_origin, &token_list))
	{
		ft_error("Error", STDERR_FILENO);
		return (NULL);
	}
	check_env_token(&token_list, env);
	set_type_the_token(&token_list);
	if (syntax_check(token_list))
	{
		printf("Syntax ERRRRRRRROR\n");
		//ft_error("Syntax error", STDERR_FILENO);
		return (NULL);
	}
	//cmd_line->token_list = token_list;
	ft_free_all_tokens(&token_list);
	return (NULL);
}
