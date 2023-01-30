/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <aboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:57:53 by aboyer            #+#    #+#             */
/*   Updated: 2023/01/30 13:41:14 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(char **cmd)
{
	char	buffer[4096];

	if (cmd[1])
	{
		printf("pwd: too many arguments\n");
		return (0);
	}
	getcwd(buffer, sizeof(buffer));
	if (buffer == NULL)
		return (perror("pwd"), 0);
	printf("%s\n", buffer);
	return (1);
}
