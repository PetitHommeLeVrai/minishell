/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <aboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:10:42 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/02 12:29:46 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tmp.h"

void	sub_dup(t_exec *exec)
{
	if (exec->id == 0)
	{
		if (exec->infile)
			dup2(exec->infile, 0);
		if (exec->outfile)
			dup2(exec->outfile, 1);
	}
	else
	{
		if (exec->infile)
			dup2(exec->infile, 0);
		else
			dup2(exec->pipe[2 * exec->id - 2], 0);
		if (exec->outfile)
			dup2(exec->outfile, 1);
		else
			dup2(exec->pipe[2 * exec->id + 1], 1);
	}
}

int	count_args(t_cmd_line *cmd_line)
{
	int	i;

	i = 0;
	while (cmd_line->word != NULL)
	{
		if (cmd_line->word->type == ARG)
			i++;
		cmd_line->word = cmd_line->word->next;
	}
	return (i);
}

char	**get_args_incmd(t_cmd_line *cmd_line)
{
	char	**cmd_args;
	int		i;

	i = 0;
	cmd_args = (char **)malloc(sizeof(char *) * (count_args(cmd_line) + 1));
	if (!cmd_args)
		return (msg_error("MALLOC ERROR\n"), NULL);
	cmd_args[count_args(cmd_line)] = NULL;
	while (cmd_line->word != NULL)
	{
		if (cmd_line->word->type == ARG)
		{
			cmd_args[i] = cmd_line->word->word;
			i++;
		}
		cmd_line->word = cmd_line->word->next;
	}
	return (cmd_args);
}

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	if (!cmd)
		return (NULL);
	if (access(cmd, 0) == 0)
		return (cmd);
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

void	child(t_exec exec, t_cmd_line *cmd_line, t_env_list *env)
{
	exec.pid = fork();
	if (!exec.pid)
	{
		get_files(&exec, cmd_line);
		sub_dup(&exec);
		close_pipes(&exec, cmd_line);
		exec.cmd_args = get_args_incmd(cmd_line);
		exec.cmd = get_cmd(exec.cmd_paths, exec.cmd_args[0]);
		if (!exec.cmd)
		{
			perror(exec.cmd_args[0]);
			free(exec.cmd_args);
			exit(127);
		}
		if (execve(exec.cmd, exec.cmd_args, exec.envp) == -1)
		{
			perror(exec.cmd_args[0]);
			free(exec.cmd);
			free(exec.cmd_args);
			exit(127);
		}
	}
}
