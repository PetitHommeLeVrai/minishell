/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:57:38 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/13 22:00:10 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char **cmd, char *value, t_env_list *env)
{
	char	buffer[4096];
	int		i;
	t_env	*env_value;

	i = chdir(value);
	if (i == -1)
	{
		printf("bash: cd: %s: No such file or directory\n", cmd[1]);
		g_ret = 127;
	}
	else
	{
		env_value = find_env_by_key(env, "PWD");
		getcwd(buffer, 4096);
		update_env_value(env, "OLDPWD", env_value->value);
		update_env_value(env, "PWD", buffer);
		g_ret = 0;
	}
}

int	cd1(t_env *env_value)
{
	if (!env_value)
	{
		printf("bash: cd: OLDPWD not set\n");
		g_ret = 1;
		return (ERROR);
	}
	return (0);
}

void	cd(char **cmd, t_env_list *env)
{
	t_env	*env_value;
	char	*value;

	if (cmd[1] == NULL || !ft_strcmp(cmd[1], "~"))
	{
		env_value = find_env_by_key(env, "HOME");
		if (!env_value)
		{
			printf("bash: cd: HOME not set\n");
			g_ret = 1;
			return ;
		}
		value = env_value->value;
	}
	else if (!ft_strcmp(cmd[1], "-"))
	{
		env_value = find_env_by_key(env, "OLDPWD");
		if (!cd1(env_value))
			return ;
		value = env_value->value;
	}
	else
		value = cmd[1];
	ft_cd(cmd, value, env);
}
