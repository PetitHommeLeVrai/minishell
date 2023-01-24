/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <aboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:24:15 by aboyer            #+#    #+#             */
/*   Updated: 2023/01/24 13:47:54 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *check_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0)
		return ("/usr/bin/echo");
	else if (ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0)
		return ("/usr/bin/pwd");
	else if (ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0)
		return ("/usr/bin/env");
	return (NULL);
}