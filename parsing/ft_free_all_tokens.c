/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 03:33:28 by ychun             #+#    #+#             */
/*   Updated: 2023/02/11 20:49:18 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_all_tokens(t_token_list *tokens)
{
	int		i;

	i = -1;
	while (++i < tokens->count)
	{
		if (tokens->token[i].word && tokens->token[i].type != T_NULL)
			free(tokens->token[i].word);
		if (tokens->token[i].origin)
			free(tokens->token[i].origin);
	}
	free(tokens->token);
	free(tokens);
}
