/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:57:44 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/14 16:53:32 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env(char **cmd, t_env_list *env_list)
{
	t_env	*tmp_env;

	(void)cmd;
	tmp_env = env_list->content;
	while (env_list)
	{
		printf("%s=%s\n", tmp_env->key, tmp_env->value);
		env_list = env_list->next;
		if (env_list)
			tmp_env = env_list->content;
	}
	exit(0);
}
