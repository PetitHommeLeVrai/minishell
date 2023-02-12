/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:57:53 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/12 19:26:13 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(char **cmd)
{
	char	buffer[4096];

	(void)cmd;
	getcwd(buffer, sizeof(buffer));
	if (buffer == NULL)
	{
		perror("pwd");
		exit(2);
	}
	printf("%s\n", buffer);
	exit(0);
}
