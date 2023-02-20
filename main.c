/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <aboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:37:15 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/17 18:03:19 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#define ERR_SYNTAX -200
#define ERR_SYNTAX_PIPE -201
#define ERR_SYNTAX_NEWLINE -202
#define ERR_AMBIGUOUS -203
struct s_global g_global;

void	con_error_status(t_token_list *tokens, int status)
{
	int	i;

	i = 0;
	if (status == ERR_SYNTAX_PIPE)
		printf ("bash: syntax error near unexpected token `%s'\n", "|");
	else if (status == ERR_SYNTAX_NEWLINE)
		printf ("bash: syntax error near unexpected token `%s'\n", "newline");
	else if (status == ERR_AMBIGUOUS)
	{
		while (tokens->token[i].type != ERR_AMBIGUOUS)
			i++;
		printf("bash: %s: ambiguous redirect\n", tokens->token[i].origin);
		g_global.ret = 1;
		ft_free_token_list(tokens);
		return ;
	}
	else if (status == -1 || status == -2 || status == ERR_SYNTAX)
		con_error_status2(tokens, status);
	g_global.ret = 2;
	if (status != -1 && status != -2)
		ft_free_token_list(tokens);
	else
		free(tokens);
}

int	is_there_space(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] != ' ')
			return (0);
	return (1);
}

void	parsing(t_env_list *env_list, char *str)
{
	t_token_list	*token_list;
	t_cmd_line		*cmd_line;
	int				status;

	if (is_there_space(str))
		return ;
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
	exec(cmd_line, env_list);
	return ;
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
	t_env_list		*env_list;

	(void)ac;
	(void)av;
	g_global.ret = 0;
	init_env_signal(envp, &env_list);
	prompt(&env_list);
	ft_free_all_env(env_list);
}
