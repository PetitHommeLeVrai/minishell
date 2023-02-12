/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:57:44 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/12 18:00:26 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env(char **cmd, t_env_list *env_list)
{
	t_env	*tmp_env;

	tmp_env = env_list->content;
	while (env_list)
	{
		printf("%s=%s\n", tmp_env->key, tmp_env->value);
		env_list = env_list->next;
		if (env_list)
			tmp_env = env_list->content;
	}
}

// typedef struct s_env t_env;
// struct s_env
// {
// 	char *var;
// 	t_env *begin;
// 	t_env *next;
// };

//Peut etre reformater pour acceder directement a 
//la liste chainé env d'une structure glogabe

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

// int main(int ac, char **av, char **envp)
// {
// 	t_env *env;

// 	env = malloc(sizeof(t_env));
// 	env->begin = env;
// 	count_lines(env, envp);
// 	get_env(env, envp);
// 	print_env(env);
// 	free_env(env);
// }