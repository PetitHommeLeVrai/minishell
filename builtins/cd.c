/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:57:38 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/20 18:54:39 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_cd(char **cmd, char *value, t_env_list **env)
{
	char	buffer[4096];
	int		i;
	t_env	*env_value;

	i = chdir(value);
	if (i == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (127);
	}
	env_value = find_env_by_key(*env, "PWD");
	getcwd(buffer, 4096);
	if (!env_value)
	{
		set_new_env(*env, "PWD", buffer);
		return (0);
	}
	update_env_value(env, "OLDPWD", env_value->value);
	update_env_value(env, "PWD", buffer);
	return (0);
}

int	cd1(t_env *env_value)
{
	if (!env_value)
	{
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
		return (0);
	}
	return (1);
}

int	cd(char **cmd, t_env_list **env)
{
	t_env	*env_value;
	char	*value;

	if (cmd[2])
		return (ft_putstr_fd("cd: too many arguments\n", 2), 1);
	if (cmd[1] == NULL || !ft_strcmp(cmd[1], "~"))
	{
		env_value = find_env_by_key(*env, "HOME");
		if (!env_value)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (1);
		}
		value = env_value->value;
	}
	else if (!ft_strcmp(cmd[1], "-"))
	{
		env_value = find_env_by_key(*env, "OLDPWD");
		if (!cd1(env_value))
			return (0);
		value = env_value->value;
	}
	else
		value = cmd[1];
	return (ft_cd(cmd, value, env));
}
