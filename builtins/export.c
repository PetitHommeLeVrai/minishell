/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:57:50 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/20 19:06:53 by ychun            ###   ########.fr       */
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
	int		j;
	char	**row_env;

	i = 0;
	if (cmd[1] == NULL)
		return (env(cmd, env_list, 1));
	while (cmd[++i])
	{
		j = -1;
		if (!check_have_equal(cmd[i]))
			return (0);
		row_env = ft_split(cmd[i], '=');
		if (check_env_argv(row_env[0]))
			return (ft_putstr_fd("export: ", 2), ft_putstr_fd(row_env[0], 2),
				ft_putstr_fd(" : not a valid indentifier\n", 2), 1);
		set_new_env(env_list, row_env[0], row_env[1]);
		while (row_env[++j])
			free(row_env[j]);
		free(row_env);
	}
	return (0);
}
