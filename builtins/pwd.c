/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <aboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:57:53 by aboyer            #+#    #+#             */
/*   Updated: 2023/01/27 15:37:40 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(void)
{
	char	buffer[4096];

	getcwd(buffer, sizeof(buffer));
	if (buffer == NULL)
		return (perror("pwd"), 0);
	printf("%s\n", buffer);
	return (1);
}
