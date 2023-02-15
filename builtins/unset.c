/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:57:55 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/15 00:58:11 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#define TMP_NULL 1
#define NEXT_NULL 2

void	free_env_list(t_env_list **env_list, t_env_list *tmp,
	t_env_list *cp, int type)
{
	if (type == TMP_NULL)
		*env_list = cp->next;
	else if (type == NEXT_NULL)
		tmp->next = NULL;
	else
		tmp->next = cp->next;
	free(cp->content->origin);
	free(cp->content->key);
	if (cp->content->value)
		free(cp->content->value);
	free(cp->content);
	cp->next = NULL;
	free(cp);
}

void	unset_env(t_env_list **env_list, char *key)
{
	t_env_list	*cp_env_list;
	t_env_list	*tmp_env_list;

	cp_env_list = *env_list;
	tmp_env_list = NULL;
	while (cp_env_list)
	{
		if (ft_strcmp(((t_env *)cp_env_list->content)->key, key) == 0)
		{
			if (!tmp_env_list)
				free_env_list(env_list, tmp_env_list, cp_env_list, TMP_NULL);
			else if (!cp_env_list->next)
				free_env_list(env_list, tmp_env_list, cp_env_list, NEXT_NULL);
			else
				free_env_list(env_list, tmp_env_list, cp_env_list, 0);
			break ;
		}
		tmp_env_list = cp_env_list;
		cp_env_list = cp_env_list->next;
	}
}

void	unset(char **cmd, t_env_list *env_list)
{
	int		i;
	char	*key;
	t_env	*env;

	i = -1;
	if (!cmd[1])
		return ;
	while (cmd[++i])
	{
		key = cmd[i];
		env = find_env_by_key(env_list, key);
		if (!env)
		{
			printf("bash: unset: `%s': not a valid identifier\n", cmd[i]);
			exit(2);
		}
		else
		{
			unset_env(&env_list, key);
			exit(0);
		}
	}
}
