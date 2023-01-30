/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 03:45:25 by ychun             #+#    #+#             */
/*   Updated: 2023/01/30 03:50:26 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



t_cmd_list	init_cmd_list(char *cmd_origin)
{
	t_token_info	token_info;

	if (cmd_tokenizer(cmd_origin, &token_info))
	{
		ft_error("Error", STDERR_FILENO);
		return (NULL);
	}
}