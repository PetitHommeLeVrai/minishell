/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <aboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:31:59 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/20 13:06:14 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_exit_free_all(int ret, t_exec *exec, t_cmd_line *line,
		t_env_list **env)
{
	parent_free(exec, line);
	ft_free_cmd_line(line);
	ft_free_all_env(env);
	exit(ret);
}

void	set_ret(int status)
{
	g_global.child = 0;
	if (WIFEXITED(status))
		g_global.ret = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		g_global.ret = WTERMSIG(status);
		if (g_global.ret != 131)
			g_global.ret = g_global.ret + 128;
	}
}

char	*check_when_no_paths(t_exec *exec, t_cmd_line *line, t_env_list **env)
{
	if (access(line->cmd_args[0], 0) != 0)
	{
		perror(line->cmd_args[0]);
		exec_exit_free_all(127, exec, line->begin, env);
	}
	isdir(exec, line, env);
	return (line->cmd_args[0]);
}

void	waiter(t_exec *exec, t_cmd_line *tmp)
{
	int	status;

	while (exec->id-- >= 0)
	{
		if (tmp->tmp != -1 && waitpid(-1, &status, 0) == tmp->tmp)
			set_ret(status);
	}
}
