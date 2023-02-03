/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <aboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:27:36 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/03 15:06:33 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tmp.h"

void	creat_pipes(t_exec *exec, t_cmd_line *cmd_line)
{
	int	i;

	i = 0;
	while (i < count_pipes(cmd_line))
	{
		if (pipe(exec->pipe + 2 * i) < 0)
			parent_free(exec);
		i++;
	}
}

void	close_pipes(t_exec *exec, t_cmd_line *cmd_line)
{
	int	i;

	i = 0;
	while (i < count_pipes(cmd_line))
	{
		close(exec->pipe[i]);
		i++;
	}
}

void	parent_free(t_exec *exec)
{
	int	i;

	i = 0;
	if (exec->cmd_paths)
		free(exec->cmd_paths);
	free(exec->pipe);
}

void	msg_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(2);
}

void	check_if_builtin(t_exec *exec, t_env_list *env_list)
{
	if (ft_strncmp(exec->cmd_args[0], "cd", 3))
		cd(exec->cmd_args, env_list);
	else if (ft_strncmp(exec->cmd_args[0], "echo", 5))
		echo(exec->cmd_args);
	else if (ft_strncmp(exec->cmd_args[0], "env", 4))
		env(env_list);
	else if (ft_strncmp(exec->cmd_args[0], "exit", 5))
		exit_cmd(exec->cmd_args);
	else if (ft_strncmp(exec->cmd_args[0], "export", 7))
		export(exec->cmd_args, env_list);
	else if (ft_strncmp(exec->cmd_args[0], "pwd", 4))
		pwd(exec->cmd_args);
	else if (ft_strncmp(exec->cmd_args[0], "unset", 6))
		unset(exec->cmd_args, env_list);
}
