/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <aboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:31:59 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/17 16:11:36 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_exit_free_all(int ret, t_exec *exec, t_cmd_line *line,
		t_env_list *env)
{
	(void)env;
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
