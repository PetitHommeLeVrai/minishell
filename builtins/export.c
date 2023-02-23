/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:57:50 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/23 16:07:49 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_substr_env(char const *s, unsigned int start, int len)
{
	size_t	i;
	int		j;
	char	*str;

	i = start;
	j = 0;
	if (s == NULL)
		return (NULL);
	if (len <= 0)
		return (NULL);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	while (i < ft_strlen(s) && j < len)
	{
		str[j] = s[i];
		j++;
		i++;
	}
	str[j] = 0;
	return (str);
}

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
	if (!key)
		return (1);
	if (!ft_strcmp(key, "$?"))
		return (0);
	if (ft_isalpha(key[0]) || key[0] == '_' || ft_isdigit(key[0]))
	{
		if (ft_isdigit(key[0]))
			return (1);
	}
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

void	ft_free_row_env(char **env)
{
	int	j;

	j = -1;
	while (env && env[++j])
		free(env[j]);
	if (env)
		free(env);
}

char	**ft_split_env(char *cmd, int *flag)
{
	int		i;
	char	**rst;

	i = -1;
	rst = (char **)malloc(sizeof(char *) * 3);
	while (cmd[++i])
	{
		if (cmd[i] == '=')
		{
			*flag = 1;
			rst[0] = ft_substr_env(cmd, 0, i);
			if (!rst[0])
				rst[0] = ft_strdup("=");
			break ;
		}
	}
	i++;
	if (*flag == 0)
	{
		rst[0] = ft_substr_env(cmd, 0, ft_strlen(cmd));
		rst[1] = NULL;
	}
	else
		rst[1] = ft_substr_env(cmd, i, ft_strlen(cmd) - i);
	rst[2] = NULL;
	return (rst);
}

int	export(char **cmd, t_env_list *env_list)
{
	int		i;
	char	**row_env;
	int		flag;

	i = 0;
	flag = 0;
	if (cmd[1] == NULL)
		return (env(cmd, env_list, 1));
	while (cmd[++i])
	{
		row_env = ft_split_env(cmd[i], &flag);
		if (check_env_argv(row_env[0]))
			return (ft_putstr_fd("export: ", 2), ft_putstr_fd(row_env[0], 2),
				ft_putstr_fd(" : not a valid identifier\n", 2),
				ft_free_row_env(row_env), 1);
		if (flag == 1)
			set_new_env(env_list, row_env[0], row_env[1]);
		ft_free_row_env(row_env);
	}
	return (0);
}
