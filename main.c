/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:37:15 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/02 21:13:48 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(t_cmd_line *cmd_line, t_env_list *env_list, char *str)
{
	cmd_line = init_cmd_list(ft_strdup(str), env_list);
}

void	prompt(t_cmd_list *cmd_list, t_env_list **env_list)
{
	char	*str;

	while (1)
	{
		str = readline("$> ");
		if (str)
			parsing(cmd_list, *env_list, str);
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

int	main(int ac, char **av, char **env)
{
	t_cmd_line	*cmd_line;
	t_env_list	*env_list;

	(void)ac;
	(void)av;
	init_env_signal(env, &env_list);
	prompt(cmd_list, &env_list);
}
