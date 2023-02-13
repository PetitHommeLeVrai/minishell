/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:37:15 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/13 02:41:16 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_ret;

void	con_error_status(t_token_list *tokens, int status)
{
	if (status == -2)
	{
		printf("Input Error\n");
		g_ret = 2;
		free(tokens);
	}
	else if (status == -1)
	{
		printf("Syntax Error\n");
		g_ret = 2;
		ft_free_token_list(tokens);
	}
}

void	parsing(t_env_list *env_list, char *str)
{
	t_token_list	*token_list;
	t_cmd_line		*cmd_line;
	int				status;

	cmd_line = NULL;
	token_list = (t_token_list *)malloc(sizeof(t_token_list));
	if (!token_list)
		ft_error("Allocation failed", STDERR_FILENO);
	status = get_token_list(str, env_list, token_list);
	if (status < 0)
	{
		con_error_status(token_list, status);
		return ;
	}
	cmd_line = init_cmd_line(cmd_line, token_list, 0);
	free(token_list->token);
	free(token_list);
	//if (exec(cmd_line, env_list))
	//	printf("Exec Error\n");
	ft_free_cmd_line(cmd_line);
}

void	prompt(t_env_list **env_list)
{
	char	*str;

	while (1)
	{
		str = readline("$> ");
		if (str)
			parsing(*env_list, str);
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
	t_env_list	*env_list;

	(void)ac;
	(void)av;
	g_ret = 0;
	init_env_signal(envp, &env_list);
	prompt(&env_list);
	ft_free_all_env(env_list);
}
