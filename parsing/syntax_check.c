/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 20:53:01 by ychun             #+#    #+#             */
/*   Updated: 2023/02/13 20:55:29 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
				|| ((tk[i + 1].type >= 30 && tk[i].type <= 33)
					|| prev.type == T_WORD)))
			return (ERROR);
		if ((tk[i].type >= 30 && tk[i].type <= 33)
			&& (tk[i + 1].type == T_NULL
				&& (tk[i + 1].type <= 40 || tk[i + 1].type >= 43)))
			return (ERROR);
		if ((tk[i].type >= 30 && tk[i].type <= 33)
			&& (tk[i + 1].type != T_NULL && tk[i + 1].type == T_WORD_NULL))
			return (ERROR);
		prev = tk[i];
	}
	return (SUCCESS);
}
