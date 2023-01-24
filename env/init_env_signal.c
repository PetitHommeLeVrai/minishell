/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_signal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 01:46:44 by ychun             #+#    #+#             */
/*   Updated: 2023/01/24 02:20:01 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		if (THAT IS FORK)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 1);
			rl_redisplay();
		}
		else
		{
			printf("\n");
		}
	}
}

void	init_list_env(t_env_list *env_list)
{
	env_list->env_list_head = ft_lstnew("", "");
	env_list->env_list_tail = ft_lstnew("", "");
	env_list->env_list_head->next = env_list->env_list_tail;
	env_list->env_list_tail->prev = env_list->env_list_head;
}

void	init_env()
{
	
}

void	init_env_signal(char **env)
{
	t_env_list	env_list;

	init_list_env(&env_list);
	init_env(env);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
