/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <aboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:57:38 by aboyer            #+#    #+#             */
/*   Updated: 2023/01/27 15:42:11 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void check_home(t_env *env)
{
	while(env->next != NULL)
	{
		if (ft_strncmp("HOME", env->var, 4) == 0)
		{
			if (chdir(env->var + 5) == -1)
			{
				perror("cd");
				return (0);
			}
			return (1);
		}
		env = env->next;
	}
	return (0);
}

int cd(char **cmd)
{
	if (!cmd[1])
	{
		if (check_home(env) == 0)
			return (0);
		return (1);
	}
	if (cmd[2])
		return (0);
	if (chdir(cmd[1]) == -1)
	{
		perror("cd");
		return (0);
	}
	return (1);
}