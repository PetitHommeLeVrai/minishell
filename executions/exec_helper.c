/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <aboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 04:28:10 by ychun             #+#    #+#             */
/*   Updated: 2023/02/17 16:57:44 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_is_builtin(t_exec *exec, t_cmd_line *cmd)
{
	if (!ft_strcmp(cmd->token[0].word, "cd"))
	{
		if (exec->pipe_nb == 1)
			return (1);
		return (-1);
	}
	else if (!ft_strcmp(cmd->token[0].word, "export"))
	{
		if (exec->pipe_nb == 1)
			return (1);
		return (-1);
	}
	else if (!ft_strcmp(cmd->token[0].word, "unset"))
	{
		if (exec->pipe_nb == 1)
			return (1);
		return (-1);
	}
	else if (!ft_strcmp(cmd->token[0].word, "exit"))
	{
		if (exec->pipe_nb == 1 || exec->id == exec->pipe_nb - 1)
			return (1);
		return (-1);
	}
	return (0);
}

int	check_if_builtin2(t_exec *exec, t_cmd_line *line, t_env_list *envp)
{
	int	ret;

	ret = -1;
	if (ft_strncmp(line->cmd_args[0], "cd", 3) == 0)
		ret = cd(line->cmd_args, envp);
	else if (ft_strncmp(line->cmd_args[0], "exit", 5) == 0)
	{
		ret = exit_cmd(line->cmd_args);
		exec_exit_free_all(ret, exec, line->begin, envp);
	}
	else if (ft_strncmp(line->cmd_args[0], "export", 7) == 0)
		ret = export(line->cmd_args, envp);
	else if (ft_strncmp(line->cmd_args[0], "unset", 6) == 0)
		ret = unset(line->cmd_args, envp);
	return (ret);
}

int	exec_helper(t_exec *exec, t_cmd_line *cmd_line, t_env_list *env_list)
{
	t_exec	exec2;
	int		builtin_status;

	exec2.id = exec->id;
	exec2.pipe_nb = exec->pipe_nb;
	exec2.pipe = exec->pipe;
	builtin_status = check_is_builtin(&exec2, cmd_line);
	if (builtin_status == 1)
	{
		get_files(&exec2, cmd_line);
		sub_dup(&exec2, cmd_line);
		cmd_line->cmd_args = get_args_incmd(cmd_line);
		g_global.ret = check_if_builtin2(exec, cmd_line, env_list);
		return (1);
	}
	if (builtin_status == 0)
		return (0);
	return (0);
}
