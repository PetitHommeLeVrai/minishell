/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 03:45:25 by ychun             #+#    #+#             */
/*   Updated: 2023/02/02 21:14:59 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd_line	init_cmd_list(char *cmd_origin, t_env_list *env)
{
	t_token_list	token_list;

	if (!init_token_list(cmd_origin, &token_list))
	{
		ft_error("Error", STDERR_FILENO);
		return (NULL);
	}
	check_env_token(&token_list, env);
	if (!syntax_check(token_list))
	{
		ft_error("Syntax error", STDERR_FILENO);
		return (NULL);
	}
}
