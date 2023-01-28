/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <aboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:57:55 by aboyer            #+#    #+#             */
/*   Updated: 2023/01/27 14:43:52 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// typedef struct s_env t_env;
// struct s_env
// {
// 	char *var;
// 	t_env *begin;
// 	t_env *next;
// };

// int	check_first(t_env *env, char *var)
// {

// 	if (ft_strncmp(env->begin->var, var, ft_strlen(var)) == 0)
// 	{
// 		env = env->next;
// 		return (1);
// 	}
// 	return (0);
// }

// int	search_var(t_env *env, char *var)
// {
// 	int l;

// 	l = ft_strlen(var);
// 	if (env->next != NULL && ft_strncmp(env->next->var, var, l) != 0)
// 		return (0);
// 	return (1);
// }

// int	unset(char **var, t_env *env)
// {
// 	int		i;
// 	t_env	*tmp;

// 	i = 0;
// 	if (!var[1])
// 		return (0);
// 	while (var[++i])
// 	{
// 		if (check_first(env, var[i]) == 1)
// 			continue ;
// 		while (search_var(env, var[i]) != 1)
// 			env = env->next;
// 		if (env->next == NULL)
// 			return (0);
// 		tmp = env->next->next;
// 		free(env->next->var);
// 		free(env->next);
// 		env->next = tmp;
// 		env = env->begin;
// 	}
// 	return (1);
// }

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

// //Peut etre reformater pour acceder directement a 
// //la liste chainé env d'une structure glogabe

// void	free_env(t_env *env)
// {
// 	t_env	*tmp;

// 	while (env != NULL)
// 	{
// 		free(env->var);
// 		if (env->next == NULL)
// 			break ;
// 		env = env->next;
// 	}
// 	env = env->begin;
// 	while (env != NULL)
// 	{
// 		tmp = env;
// 		env = env->next;
// 		free(tmp);
// 	}
// }

// int	get_env(t_env *env, char **envp)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (envp[i])
// 	{
// 		env->var = (char *)malloc(sizeof(char) * ft_strlen(envp[i]) + 1);
// 		if (!env->var)
// 			return (0);
// 		while (envp[i][j])
// 		{
// 			env->var[j] = envp[i][j];
// 			j++;
// 		}
// 		env->var[j] = '\0';
// 		if (env->next != NULL)
// 			env = env->next;
// 		j = 0;
// 		i++;
// 	}
// 	env = env->begin;
// 	return (0);
// }

// void	print_env(t_env *env)
// {
// 	while (env != NULL)
// 	{
// 		printf("%s\n", env->var);
// 		if (env->next == NULL)
// 			break ;
// 		env = env->next;
// 	}
// 	env = env->begin;
// }

// int count_lines(t_env *env, char **envp)
// {
// 	int i = 0;

// 	while (envp[i])
// 	{
// 		env->next = malloc(sizeof(t_env));
// 		env->next->begin = env->begin;
// 		if (envp[i + 1] != NULL)
// 			env = env->next;
// 		else
// 			free(env->next);
// 		i++;
// 	}
// 	env->next = NULL;
// 	env = env->begin;
// 	return (i);
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
// 	char *test3 = "unset LANGUAGE=en";
// 	char *test = "export LOL=CACA LOL2=caca";
// 	char **test2;
// 	char **test4;
// 	env = malloc(sizeof(t_env));
// 	env->begin = env;
// 	count_lines(env, envp);
// 	get_env(env, envp);
// 	print_env(env);
// 	printf("\n\n");
// 	test2 = ft_split(test, ' ');
// 	export(test2, env);
// 	print_env(env);
// 	printf("\n\n");
// 	test4 = ft_split(test3, ' ');
// 	unset(test4, env);
// 	print_env(env);
// 	printf("\n\n");
// 	free_split(test2);
// 	free_split(test4);
// 	free_env(env);
// }