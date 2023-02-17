/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 04:28:10 by ychun             #+#    #+#             */
/*   Updated: 2023/02/17 05:39:22 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_is_builtin(t_cmd_line *cmd)
{
	if (!ft_strcmp(cmd->token[0].word, "pwd"))
		return (0);
	else if (!ft_strcmp(cmd->token[0].word, "env"))
		return (0);
	else if (!ft_strcmp(cmd->token[0].word, "echo"))
		return (0);
	else if (!ft_strcmp(cmd->token[0].word, "cd"))
		return (1);
	else if (!ft_strcmp(cmd->token[0].word, "export"))
		return (1);
	else if (!ft_strcmp(cmd->token[0].word, "unset"))
		return (1);
	else if (!ft_strcmp(cmd->token[0].word, "exit"))
		return (500);
	return (-1);
}

int	check_if_builtin2(t_exec *exec, t_cmd_line *line, t_env_list *envp)
{
	int	ret;

	ret = -1;
	(void)exec;
	if (ft_strncmp(line->cmd_args[0], "cd", 3) == 0)
		ret = cd(line->cmd_args, envp);
	else if (ft_strncmp(line->cmd_args[0], "echo", 5) == 0)
		ret = echo(line->cmd_args);
	else if (ft_strncmp(line->cmd_args[0], "env", 4) == 0)
		ret = env(line->cmd_args, envp, 0);
	else if (ft_strncmp(line->cmd_args[0], "exit", 5) == 0)
		ret = exit_cmd(line->cmd_args);
	else if (ft_strncmp(line->cmd_args[0], "export", 7) == 0)
		ret = export(line->cmd_args, envp);
	else if (ft_strncmp(line->cmd_args[0], "pwd", 4) == 0)
		ret = pwd(line->cmd_args);
	else if (ft_strncmp(line->cmd_args[0], "unset", 6) == 0)
		ret = unset(line->cmd_args, envp);
	return (ret);
}

int	exec_helper(t_cmd_line *cmd_line, t_env_list *env_list)
{
	t_exec		exec;
	int			builtin_status;

	builtin_status = check_is_builtin(cmd_line);
	if (builtin_status == 1)
	{
		exec.cmd_paths = ft_split(get_path(env_list), ':');
		exec.id = -1;
		exec.envp = create_envp_char(env_list);
		get_files(&exec, cmd_line);
		sub_dup(&exec, cmd_line);
		cmd_line->cmd_args = get_args_incmd(cmd_line);
		g_global.ret = check_if_builtin2(&exec, cmd_line, env_list);
		parent_free(&exec, cmd_line);
	}
	else
		return (1);
	//if (cmd_line->next)
	//{
		//cmd_line = cmd_line->next;
		//return (1);
	//}
	return (0);
}
