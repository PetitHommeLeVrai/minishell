/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_cmd_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 05:33:51 by ychun             #+#    #+#             */
/*   Updated: 2023/02/12 05:36:22 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_cmd_line(t_cmd_line *cmd_line)
{
	int	i;

	i = -1;
	while (cmd_line->token[i].type != T_NULL)
	{
		if (cmd_line->token[i].word)
			free(cmd_line->token[i].word);
		if (cmd_line->token[i].origin)
			free(cmd_line->token[i].origin);
	}
	free(cmd_line->token);
	free(cmd_line);
}
