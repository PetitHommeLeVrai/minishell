/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <aboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:05:41 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/14 16:18:03 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void check_2(char *cmd)
{
	if ((cmd[0] == '.' && cmd[1] == '/') || cmd[0] == '/')
	{			
		if (access(cmd, 0) != 0)
		{
			perror(cmd);
			exit(127);
		}
	}
}

void	check_is_absolute_path(char *cmd, int flag)
{
	if (ft_strlen(cmd) == 1 && cmd[0] == '.')
	{
		ft_putstr_fd(".: filename argument required\n", 2);
		exit(2);
	}
	if (flag == 0)
	{
		if (cmd[0] == '.' || (cmd[0] == '.' && cmd[1] == '/') || cmd[0] == '/')
		{
			if (access(cmd, 0) != 0)
			{
				perror(cmd);
				exit(127);
			}
		}
	}
	if (flag == 1)
	{
		check_2(cmd);
	}
}

int get_flag(t_cmd_line *cmd_line)
{
	int i;

	i = 0;
	while (i < cmd_line->token_count)
	{
		if (cmd_line->token[i].type == ARG)
			return (cmd_line->token[i].flag_quotes);
		i++;
	}
	return (0);
}