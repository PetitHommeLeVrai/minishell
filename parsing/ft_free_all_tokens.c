/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 03:33:28 by ychun             #+#    #+#             */
/*   Updated: 2023/02/06 01:21:26 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_all_tokens(t_token_list *tokens)
{
	int		i;
	t_token	*tmp_token;

	i = -1;
	tmp_token = tokens->token;
	while (++i < tokens->count)
	{
		free(tmp_token[i].word);
		if (tmp_token[i].origin)
			free(tmp_token[i].origin);
	}
	free(tokens->token);
}
