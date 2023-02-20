/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <aboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:37:15 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/20 18:06:38 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_global	g_global;

int	is_there_space(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] != ' ')
			return (0);
	return (1);
}

void	parsing(t_env_list **env_list, char *str)
{
	t_token_list	*token_list;
	t_cmd_line		*cmd_line;
	int				status;

	if (is_there_space(str))
		return ;
	status = check_quotes_incmd(str);
	if (status < 0)
	{
		con_error_status2(status);
		return ;
	}
	cmd_line = NULL;
	token_list = (t_token_list *)malloc(sizeof(t_token_list));
	if (!token_list)
		ft_error("Allocation failed", STDERR_FILENO);
	status = get_token_list(str, *env_list, token_list);
	if (status < 0)
	{
		con_error_status(token_list, status);
		return ;
	}
	cmd_line = init_cmd_line(cmd_line, token_list);
	ft_free_token_list2(token_list);
	exec(cmd_line, env_list);
}

void	prompt(t_env_list **env_list)
{
	char	*str;

	while (1)
	{
		str = readline("$> ");
		if (str)
			parsing(env_list, str);
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
	t_env_list		*env_list;

	if (ac > 1)
	{
		printf("Too many arguments. Usage: ./minishell\n");
		return (1);
	}
	(void)av;
	g_global.child = 0;
	g_global.ret = 0;
	init_env_signal(envp, &env_list);
	prompt(&env_list);
	rl_clear_history();
	ft_free_all_env(&env_list);
}
