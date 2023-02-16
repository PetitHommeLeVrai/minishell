/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 21:19:38 by ychun             #+#    #+#             */
/*   Updated: 2023/02/16 15:01:11 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd_line	*new_cmd_line(void)
{
	t_cmd_line	*new_cmds;

	new_cmds = (t_cmd_line *)malloc(sizeof(t_cmd_line));
	if (!new_cmds)
		ft_error("Allocation error", STDERR_FILENO);
	new_cmds->begin = NULL;
	new_cmds->token = NULL;
	new_cmds->next = NULL;
	new_cmds->infile = -1;
	new_cmds->outfile = -1;
	new_cmds->cmd_args = NULL;
	return (new_cmds);
}

int	count_token_before_pipe(t_token *token, int i)
{
	int	j;

	j = i;
	while (token[i].type != T_NULL)
	{
		if (token[i].type == T_PIPE)
			break ;
		i++;
	}
	return (i - j);
}

t_cmd_line	*init_cmd_line(t_cmd_line *cmd_line_origin,
	t_token_list *tokens, int i)
{
	int			count_token;
	t_cmd_line	*cmd_line;
	t_token		new_token;
	int			j;

	j = 0;
	cmd_line = new_cmd_line();
	count_token = count_token_before_pipe(tokens->token, i);
	cmd_line->token_count = count_token;
	cmd_line->token = (t_token *)malloc(sizeof(t_token) * (count_token + 1));
	while (tokens->token[i].type != T_NULL && tokens->token[i].type != T_PIPE)
	{
		new_token = tokens->token[i++];
		cmd_line->token[j++] = new_token;
	}
	cmd_line->token[j].type = T_NULL;
	cmd_line_origin = cmd_line;
	cmd_line_origin->next = NULL;
	if (tokens->token[i].type == T_PIPE)
	{
		cmd_line_origin->next = init_cmd_line(cmd_line_origin->next,
				tokens, i + 1);
		free(tokens->token[i].word);
	}
	return (cmd_line_origin);
}
