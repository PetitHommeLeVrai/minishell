/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:27:36 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/13 05:28:57 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_pipes(t_exec *exec, t_cmd_line *cmd_line)
{
	int	i;

	i = 0;
	while (i < count_pipes(cmd_line))
	{
		if (pipe(exec->pipe + 2 * i) < 0)
			parent_free(exec, cmd_line);
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

void	parent_free(t_exec *exec, t_cmd_line *line)
{
	if (exec->cmd_paths)
		free(exec->cmd_paths);
	free(exec->pipe);
	free(exec->envp);
	while (line != NULL)
	{
		if (line->cmd_args)
			free(line->cmd_args);
		close(line->infile);
		close(line->outfile);
		line->infile = -1;
		line->outfile = -1;
		line->pipe_nb = -1;
		line = line->next;
	}
}

void	msg_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(2);
}

void	check_if_builtin(t_cmd_line *line, t_env_list *envp)
{
	if (ft_strncmp(line->cmd_args[0], "cd", 3))
		cd(line->cmd_args, envp);
	else if (ft_strncmp(line->cmd_args[0], "echo", 5))
		echo(line->cmd_args);
	else if (ft_strncmp(line->cmd_args[0], "env", 4))
		env(line->cmd_args, envp);
	else if (ft_strncmp(line->cmd_args[0], "exit", 5))
		exit_cmd(line->cmd_args);
	else if (ft_strncmp(line->cmd_args[0], "export", 7))
		export(line->cmd_args, envp);
	else if (ft_strncmp(line->cmd_args[0], "pwd", 4))
		pwd(line->cmd_args);
	else if (ft_strncmp(line->cmd_args[0], "unset", 6))
		unset(line->cmd_args, envp);
}
