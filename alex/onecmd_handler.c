/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   onecmd_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <aboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:12:41 by aboyer            #+#    #+#             */
/*   Updated: 2023/01/24 13:50:03 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_paths(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("PATH", envp[i], 4) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	if (!paths)
		return ;
	while (paths[i] != NULL)
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

char	*get_command(char **paths, char *cmd)
{
	char	*temp;
	char	*command;
	int		i;

	i = 0;
	if (!paths)
		return (check_builtin(cmd));
	if (!cmd)
		return (NULL);
	if (access(cmd, 0) == 0)
		return (cmd);
	while (paths[i] != NULL)
	{
		temp = ft_strjoin(paths[i], "/");
		command = ft_strjoin(temp, cmd);
		free(temp);
		if (access(command, 0) == 0)
			return (command);
		else
			free(command);
		i++;
	}
	return (NULL);
}

int	cmd_handler(char *cmd, char **envp)
{
	char	**cmds_paths;
	char	**cmd_args;
	char	*command;

	cmds_paths = ft_split(find_paths(envp), ':');
	cmd_args = ft_split(cmd, ' ');
	command = get_command(cmds_paths, cmd_args[0]);
	if (!command)
	{
		printf("command not found\n");
		free_paths(cmd_args);
		free_paths(cmds_paths);
		return (0);
	}
	if (execve(command, cmd_args, envp) < 0)
	{
		free_paths(cmd_args);
		free_paths(cmds_paths);
		printf("execve error\n");
		return (0);
	}
	return (1);
}

int main(int ac, char **av, char **envp)
{
	cmd_handler(av[1], envp);
}
