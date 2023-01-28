/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <aboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:57:46 by aboyer            #+#    #+#             */
/*   Updated: 2023/01/27 16:04:41 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_atoi_exit(const char *nptr)
{
	int	result;
	int	neg;
	int	i;

	result = 0;
	neg = 1;
	i = 0;
	while ((nptr[i] == ' ') || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-')
	{
		neg = neg * -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result * neg);
}

void ft_exit(char **cmd)
{
	int nb;
	
	if (!cmd[1])
		exit(0);
	if (cmd[2])
	{
		printf("exit: too many arguments");
		return ;
	}
	nb = ft_atoi_exit(cmd[1]);
	if (nb < 0)
		exit((unsigned int)nb);
	else if (nb > 255)
		exit(nb % 256);
}
