/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:10:42 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/17 01:52:07 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_args(t_cmd_line *cmd_line)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < cmd_line->token_count)
	{
		if (cmd_line->token[i].type == ARG)
			count++;
		i++;
	}
	return (count);
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
	while (i < cmd_line->token_count)
	{
		if (cmd_line->token[i].type == ARG)
			cmd_args[i] = cmd_line->token[i].word;
		i++;
	}
	return (cmd_args);
}

char	*get_cmd(t_exec *exec, t_cmd_line *line, t_env_list *env)
{
	char	*tmp;
	char	*command;
	int		i;

	i = 0;
	if (!line->cmd_args[0] || line->cmd_args[0][0] == '\0')
		return (NULL);
	check_is_absolute_path(exec, line, env);
	if (access(line->cmd_args[0], 0) == 0)
		return (line->cmd_args[0]);
	if (!exec->cmd_paths)
		return (NULL);
	while (exec->cmd_paths[i])
	{
		tmp = ft_strjoin(exec->cmd_paths[i], "/");
		command = ft_strjoin(tmp, line->cmd_args[0]);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}

char	**create_envp_char(t_env_list *env)
{
	char		**envp;
	t_env_list	*tmp;
	int			i;

	i = 0;
	tmp = env;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	envp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!envp)
		return (msg_error("envp alloc error\n"), NULL);
	envp[i] = NULL;
	i = 0;
	while (env != NULL)
	{
		envp[i] = env->content->origin;
		env = env->next;
		i++;
	}
	return (envp);
}

void	child(t_exec exec, t_cmd_line *cmd_line, t_env_list *env)
{
	g_global.child = 1;
	exec.pid = fork();
	if (!exec.pid)
	{
		exec.flag = get_flag(cmd_line);
		get_files(&exec, cmd_line);
		sub_dup(&exec, cmd_line);
		close_pipes(&exec, cmd_line);
		cmd_line->cmd_args = get_args_incmd(cmd_line);
		check_if_builtin(&exec, cmd_line, env);
		exec.cmd = get_cmd(&exec, cmd_line, env);
		if (!exec.cmd)
			put_right_message(&exec, cmd_line, env);
		if (execve(exec.cmd, cmd_line->cmd_args, exec.envp) == -1)
		{
			perror(cmd_line->cmd_args[0]);
			exit(127);
		}
	}
}
