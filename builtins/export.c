/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:57:50 by aboyer            #+#    #+#             */
/*   Updated: 2023/01/30 00:30:11 by ychun            ###   ########.fr       */
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
			ft_error("Allocation memory failed", STDERR_FILENO);
	}
	else
		*value = NULL;
}

int	check_env_argv(char *key)
{
	int	i;

	i = -1;
	if (key == "$?")
		return (1);
	while (key[++i])
	{
		if (ft_isalpha(key[i]) && key[i] == '_' && ft_isdigit(key[i]))
			return (0);
	}
	return (1);
}

void	export(t_cmd *cmd, t_env_list *env_list)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	if (cmd->cmd_argv[1] == NULL)
	{
		show_env();
		exit(0);
	}
	while (cmd->cmd_argv[++i])
	{
		key = NULL;
		value = NULL;
		seperate_env_argv(cmd->cmd_argv[i], &key, &value);
		if (check_env_argv(key))
			ft_error("Minishell", STDERR_FILENO);
		else
			set_new_env(&env_list, key, value);
		free(key);
		free(value);
	}
}

// int	export(char **var, t_env *env)
// {
// 	int	i;

// 	i = 1;
// 	if (!var[i])
// 		return (0);
// 	while (var[i])
// 	{
// 		while (env->next != NULL)
// 			env = env->next;
// 		env->next = malloc(sizeof(t_env));
// 		if (env->next == NULL)
// 			return (0);
// 		env->next->begin = env->begin;
// 		env->next->var = ft_strdup(var[i]);
// 		env->next->next = NULL;
// 		env = env->begin;
// 		i++;
// 	}
// 	return (1);
// }

// void free_split(char **strs)
// {
// 	int i = 0;

// 	while (strs[i])
// 	{
// 		free(strs[i]);
// 		i++;
// 	}
// 	free(strs);
// }

// int main(int ac, char **av, char **envp)
// {
// 	t_env *env;
// 	char *test = "export LOL=CACA LOL2=caca";
// 	char **test2;
// 	env = malloc(sizeof(t_env));
// 	env->begin = env;
// 	count_lines(env, envp);
// 	get_env(env, envp);
// 	print_env(env);
// 	test2 = ft_split(test, ' ');
// 	export(test2, env);
// 	print_env(env);
// 	free_split(test2);
// 	free_env(env);
// }