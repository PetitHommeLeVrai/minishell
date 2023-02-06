/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:37:15 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/06 01:46:39 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(t_cmd_line *cmd_line, t_env_list *env_list, char *str)
{
	cmd_line = init_cmd_line(str, env_list);
}

void	prompt(t_cmd_line *cmd_line, t_env_list **env_list)
{
	char	*str;

	while (1)
	{
		str = readline("$> ");
		if (str)
		{
			//printf("***** readline return : %s *****\n", str);
			parsing(cmd_line, *env_list, str);
		}
		else
		{
			printf("exit\n");
			break ;
		}
		if (ft_strcmp(str, ""))
			add_history(str);
		free(str);
		str = NULL;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_cmd_line	*cmd_line;
	t_env_list	*env_list;

	(void)ac;
	(void)av;
	cmd_line = NULL;
	init_env_signal(envp, &env_list);
	prompt(cmd_line, &env_list);
	ft_free_all_env(env_list);
}
