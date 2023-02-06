/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 20:53:01 by ychun             #+#    #+#             */
/*   Updated: 2023/02/06 00:50:09 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	syntax_check(t_token_list token_list)
{
	int		i;
	t_token	*tk;
	t_token	prev;

	tk = token_list.token;
	prev.word = NULL;
	prev.type = 0;
	prev.origin = NULL;
	i = -1;
	while (++i < token_list.count)
	{
		if (tk[i].type == T_PIPE
			&& (prev.word == NULL || tk[i + 1].type == T_NULL
				|| prev.type != T_WORD || tk[i + 1].type == T_PIPE))
			return (ERROR);
		if (tk[i].type == T_REDIRECTION
			&& (tk[i + 1].type == T_NULL || tk[i + 1].type != T_WORD))
			return (ERROR);
		if (tk[i].type == T_REDIRECTION
			&& (tk[i + 1].type != T_NULL && tk[i + 1].type == T_WORD_NULL))
			return (ERROR);
		prev = tk[i];
	}
	return (SUCCESS);
}
