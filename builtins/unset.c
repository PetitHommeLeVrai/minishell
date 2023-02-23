/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:57:55 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/23 03:13:23 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#define PREV 1000
#define NEXT 2000

void	free_env_list(t_env_list **target)
{
	free(((t_env *)((*target)->content))->origin);
	free(((t_env *)((*target)->content))->key);
	if (((t_env *)((*target)->content))->value != NULL)
		free(((t_env *)((*target)->content))->value);
	free(((*target)->content));
	(*target)->next = NULL;
	free(*target);
}

void	delete_list_by_key(t_env_list **list,
		t_env_list **prev, t_env_list **curr)
{
	if ((*prev) == NULL)
	{
		*list = (*curr)->next;
		free_env_list(curr);
	}
	else if ((*curr)->next == NULL)
	{
		(*prev)->next = NULL;
		free_env_list(curr);
	}
	else
	{
		(*prev)->next = (*curr)->next;
		free_env_list(curr);
	}
}

void	unset_env(t_env_list **env_list, char *target_key)
{
	t_env_list	*curr;
	t_env_list	*prev;

	curr = *env_list;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(((t_env *)((curr)->content))->key, target_key) == 0)
		{
			delete_list_by_key(env_list, &prev, &curr);
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	unset(char **cmd, t_env_list **env_list)
{
	int		i;
	char	*key;
	t_env	*env;

	i = 0;
	if (!cmd[1])
		return (0);
	while (cmd[++i])
	{
		key = cmd[i];
		env = find_env_by_key(*env_list, key);
		if (!env)
		{
			ft_putstr_fd("unset: '", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (2);
		}
		else
			unset_env(env_list, key);
	}
	return (0);
}
