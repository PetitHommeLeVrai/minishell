/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:31:59 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/20 02:09:30 by ychun            ###   ########.fr       */
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
