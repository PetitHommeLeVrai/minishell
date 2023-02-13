/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <aboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:27:36 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/13 15:25:04 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_pipes(t_exec *exec, t_cmd_line *cmd_line)
{
	int	i;

	i = 0;
	while (i < exec->pipe_nb)
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
	(void)cmd_line;
	while (i < exec->pipe_nb * 2)
	{
		close(exec->pipe[i]);
		i++;
	}
}

void	parent_free(t_exec *exec, t_cmd_line *line)
{
	int	i;

	i = -1;
	if (exec->cmd_paths)
	{
		while (exec->cmd_paths[++i])
			free(exec->cmd_paths[i]);
		free(exec->cmd_paths);
	}
	free(exec->pipe);
	free(exec->envp);
	while (line != NULL)
	{
		if (line->cmd_args)
			free(line->cmd_args);
		if (line->infile >= 0)
			close(line->infile);
		if (line->outfile >= 0)
			close(line->outfile);
		line->infile = -1;
		line->outfile = -1;
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
	if (ft_strncmp(line->cmd_args[0], "cd", 3) == 0)
		cd(line->cmd_args, envp);
	else if (ft_strncmp(line->cmd_args[0], "echo", 5) == 0)
		echo(line->cmd_args);
	else if (ft_strncmp(line->cmd_args[0], "env", 4) == 0)
		env(line->cmd_args, envp);
	else if (ft_strncmp(line->cmd_args[0], "exit", 5) == 0)
		exit_cmd(line->cmd_args);
	else if (ft_strncmp(line->cmd_args[0], "export", 7) == 0)
		export(line->cmd_args, envp);
	else if (ft_strncmp(line->cmd_args[0], "pwd", 4) == 0)
		pwd(line->cmd_args);
	else if (ft_strncmp(line->cmd_args[0], "unset", 6) == 0)
		unset(line->cmd_args, envp);
}
