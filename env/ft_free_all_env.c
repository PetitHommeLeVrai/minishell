/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 18:23:50 by ychun             #+#    #+#             */
/*   Updated: 2023/02/04 18:48:39 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_free_all_env_list(t_env_list *env_list)
{
	t_env_list	*tmp;
	t_env_list	*target;

	target = env_list;
	tmp = target;
	while (target)
	{
		tmp = tmp->next;
		free(target);
		target = tmp;
	}
}

void	ft_free_all_env(t_env_list *env_list)
{
	t_env_list	*tmp;

	tmp = env_list;
	while (env_list)
	{
		free(env_list->content->origin);
		free(env_list->content->key);
		if (env_list->content->value)
			free(env_list->content->value);
		free(env_list->content);
		env_list = env_list->next;
	}
	ft_free_all_env_list(tmp);
}
