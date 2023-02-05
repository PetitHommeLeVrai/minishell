/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_new_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 00:09:40 by ychun             #+#    #+#             */
/*   Updated: 2023/02/05 03:06:45 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_value_by_key(t_env_list *env_list, char *key)
{
	t_env	*env;
	char	*value;

	env = find_env_by_key(env_list, key);
	if (!env)
		value = ft_strdup("");
	else
		value = ft_strdup(env->value);
	if (!value)
		ft_error("Allocation error", STDERR_FILENO);
	return (value);
}

t_env	*find_env_by_key(t_env_list *env_list, char *key)
{
	t_env_list	*tmp_list;
	int			i;

	i = 0;
	tmp_list = env_list;
	while (tmp_list)
	{
		if (ft_strcmp(((t_env *)tmp_list->content)->key, key) == 0)
			return (tmp_list->content);
		tmp_list = tmp_list->next;
	}
	return (NULL);
}

void	get_new_env(t_env_list **env, char *key, char *value)
{
	t_env_list	*new_list;
	t_env		*new_env;
	char		*origin;

	new_env = ft_new_env();
	new_list = ft_lstnew(new_env);
	if (value)
	{
		origin = ft_strjoin(key, "=");
		origin = ft_strjoin(origin, value);
	}
	else
		origin = ft_strdup(key);
	new_env->origin = origin;
	new_env->key = ft_strdup(key);
	if (!new_list || !new_env || !origin)
		ft_error("Allocation error", STDERR_FILENO);
	if (value)
		new_env->value = ft_strdup(value);
	ft_lstadd_back(env, new_list);
}

void	get_new_env_value(t_env *env, char *key, char *value)
{
	char	*origin;

	if (value)
	{
		origin = ft_strjoin(key, "=");
		origin = ft_strjoin(origin, value);
	}
	else
		origin = ft_strdup(key);
	if (!origin)
		ft_error("Allocation error", STDERR_FILENO);
	env->origin = origin;
	env->key = ft_strdup(key);
	if (value)
		env->value = ft_strdup(value);
}

void	set_new_env(t_env_list **env_list, char *key, char *value)
{
	t_env	*new_env;

	new_env = find_env_by_key(*env_list, key);
	if (!new_env)
		get_new_env(env_list, key, value);
	else
	{
		free(new_env->origin);
		free(new_env->key);
		if (new_env->value)
			free(new_env->value);
		get_new_env_value(new_env, key, value);
	}
}
