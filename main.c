/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:37:15 by aboyer            #+#    #+#             */
/*   Updated: 2023/01/24 01:57:18 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(t_cmd_list *cmd_list)
{

}

void	prompt(t_cmd_list *cmd_list)
{
	char	*str;

	while (1)
	{
		str = readline("$> ");
		if (str)
			parsing(cmd_list);
		else
		{
			printf("exit\n");
			break ;
		}
		add_history(str);
		free(str);
		str = NULL;
	}
}

int	main(int ac, char **av, char **env)
{
	t_cmd_list	*cmd_list;

	(void)ac;
	(void)av;
	init_env_signal(env);
	prompt(cmd_list);
}
