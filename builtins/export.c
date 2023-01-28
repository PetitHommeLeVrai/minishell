/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <aboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:57:50 by aboyer            #+#    #+#             */
/*   Updated: 2023/01/27 14:44:01 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

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