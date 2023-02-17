/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs_utils_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <aboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:13:08 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/17 14:13:36 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	isdir(t_exec *exec, t_cmd_line *line, t_env_list *env)
{
	struct stat	path;

	stat(line->cmd_args[0], &path);
	if (S_ISREG(path.st_mode) == 0)
	{
		ft_putstr_fd(line->cmd_args[0], 2);
		ft_putstr_fd(": Is a directory\n", 2);
		exec_exit_free_all(126, exec, line->begin, env);
	}
}
