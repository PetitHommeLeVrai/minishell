/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <aboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:05:41 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/14 14:06:30 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_is_absolute_path(char *cmd)
{
	if (ft_strlen(cmd) == 1 && cmd[0] == '.')
	{
		ft_putstr_fd(".: filename arguement required\n", 2);
		exit(2);
	}
	if (cmd[0] == '.' || (cmd[0] == '.' && cmd[1] == '/') || cmd[0] == '/')
	{
		if (access(cmd, 0) != 0)
		{
			perror(cmd);
			exit(127);
		}
	}
}
