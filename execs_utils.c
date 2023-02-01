/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <aboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:27:36 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/01 14:06:53 by aboyer           ###   ########.fr       */
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
