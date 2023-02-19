/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:57:50 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/19 16:50:40 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	seperate_env_argv(char *argv, char **key, char **value)
{
	int	i;

	i = -1;
	while (argv[i] && argv[i] != '=')
	{
		if (argv[i] == '=')
			break ;
	}
	*key = ft_substr(argv, 0, i);
	if (ft_strlen(argv) - i)
	{
		*value = ft_substr(argv, i + 1, ft_strlen(argv) - i);
		if (!(*key) || !(*value))
			ft_error("Allocation failed", STDERR_FILENO);
	}
	else
		*value = NULL;
}

int	check_env_argv(char *key)
{
	int	i;

	i = -1;
	if (!ft_strcmp(key, "$?"))
		return (0);
	while (key[++i])
	{
		if (!ft_isalpha(key[i]) && key[i] != '_' && !ft_isdigit(key[i]))
			return (1);
	}
	return (0);
}

int	check_have_equal(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
		if (cmd[i] == '=')
			return (1);
	return (0);
}

int	export(char **cmd, t_env_list *env_list)
{
	int		i;
	char	**row_env;

	i = -1;
	if (cmd[1] == NULL)
	{
		env(cmd, env_list, 1);
		return (0);
	}
	if (!check_have_equal(cmd[1]))
		return (0);
	row_env = ft_split(cmd[1], '=');
	if (check_env_argv(row_env[0]))
	{
		printf("export: `%s': not a valid identifier\n", row_env[0]);
		return (1);
	}
	set_new_env(env_list, row_env[0], row_env[1]);
	while (row_env[++i])
		free(row_env[i]);
	free(row_env);
	return (0);
}
