/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:11:32 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/12 19:34:06 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_pipes(t_cmd_line *cmd_line)
{
	int	i;

	i = 0;
	while (cmd_line != NULL)
	{
		i++;
		cmd_line = cmd_line->next;
	}
	return (i * 2);
}

int	count_env_vars(t_env_list *env)
{
	int	i;

	i = 0;
	while (env != NULL)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	*get_path(t_env_list *env)
{
	while (env != NULL)
	{
		if (ft_strncmp("PATH", env->content->key, 5) == 0)
			return (env->content->value);
		env = env->next;
	}
	return (NULL);
}

int	exec(t_cmd_line *cmd_line, t_env_list *env)
{
	int			status;
	t_exec		exec;
	t_cmd_line	*tmp;

	exec.pipe = (int *)malloc(sizeof(int) * count_pipes(cmd_line));
	cmd_line->pipe_nb = count_pipes(cmd_line);
	if (!exec.pipe)
		ft_error("Allocation error", STDERR_FILENO);
	exec.cmd_paths = ft_split(get_path(env), ':');
	//create_pipes(&exec, cmd_line);
	exec.id = 0;
	exec.envp = create_envp_char(env);
	tmp = cmd_line;
	while (exec.id < count_pipes(cmd_line))
	{
		//child(exec, cmd_line, env);
		tmp = tmp->next;
		exec.id++;
	}
	close_pipes(&exec, cmd_line);
	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
		g_ret = WEXITSTATUS(status);
	parent_free(&exec, cmd_line);
	return (1);
}
