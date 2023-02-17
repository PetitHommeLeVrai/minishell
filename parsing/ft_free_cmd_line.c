/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_cmd_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 05:33:51 by ychun             #+#    #+#             */
/*   Updated: 2023/02/17 21:45:18 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_token_list(t_token_list *tokens)
{
	int		i;
	t_token	*tmp;

	i = -1;
	tmp = tokens->token;
	while (tmp[++i].tail != 1)
	{
		if (tmp[i].word)
			free(tmp[i].word);
		if (tmp[i].origin)
			free(tmp[i].origin);
	}
	free(tokens->token);
	free(tokens);
}

void	ft_free_cmd_line(t_cmd_line *cmd_line)
{
	int			i;
	t_cmd_line	*tmp_line;
	t_cmd_line	*prev_line;

	tmp_line = cmd_line;
	while (tmp_line)
	{
		i = -1;
		while (tmp_line->token[++i].type != T_NULL)
		{
			if (tmp_line->token[i].word)
				free(tmp_line->token[i].word);
			if (tmp_line->token[i].origin)
				free(tmp_line->token[i].origin);
		}
		free(tmp_line->token);
		prev_line = tmp_line;
		tmp_line = tmp_line->next;
		free(prev_line);
	}
}
