/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_new_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 00:09:40 by ychun             #+#    #+#             */
/*   Updated: 2023/01/30 00:29:29 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*find_env_by_key(t_env_list *env_list, char *key)
{
	t_env_list	*tmp_list;

	tmp_list = env_list;
	while (tmp_list)
	{
		if (ft_strcmp(((t_env *)tmp_list->content)->key, key))
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
		get_new_env(new_env, key, value);
	}
}
