/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:57:50 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/15 00:56:43 by ychun            ###   ########.fr       */
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
		if (!*key || !*value)
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
		return (1);
	while (key[++i])
	{
		if (ft_isalpha(key[i]) && key[i] == '_' && ft_isdigit(key[i]))
			return (0);
	}
	return (1);
}

void	export(char **cmd, t_env_list *env_list)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	if (cmd[1] == NULL)
	{
		env(cmd, env_list);
		exit(0);
	}
	while (cmd[++i])
	{
		key = NULL;
		value = NULL;
		seperate_env_argv(cmd[i], &key, &value);
		if (check_env_argv(key))
			printf("bash: export: `%s': not a valid identifier\n", cmd[i]);
		set_new_env(&env_list, key, value);
		free(key);
		free(value);
		exit(0);
	}
}
