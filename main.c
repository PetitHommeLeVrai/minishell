/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:37:15 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/12 05:36:29 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_ret;

void	parsing(t_cmd_line *cmd_line, t_env_list *env_list, char *str)
{
	t_token_list	*token_list;

	token_list = (t_token_list *)malloc(sizeof(t_token_list));
	if (!token_list)
		ft_error("Allocation failed", STDERR_FILENO);
	if (get_token_list(str, env_list, token_list))
	{
		printf("Error\n");
		g_ret = 2;
	}
	cmd_line = init_cmd_line(cmd_line, token_list, 0);
	free(token_list->token);
	free(token_list);
	ft_free_cmd_line(cmd_line);
}

void	prompt(t_cmd_line *cmd_line, t_env_list **env_list)
{
	char	*str;

	while (1)
	{
		str = readline("$> ");
		if (str)
		{
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
	g_ret = 0;
	init_env_signal(envp, &env_list);
	prompt(cmd_line, &env_list);
	ft_free_all_env(env_list);
}
