/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <aboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:57:46 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/10 12:34:10 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	ft_atoi_exit(const char *nptr)
{
	long long	result;
	int			neg;
	int			i;

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

int	check_long_long(char *num)
{
	if (num[0] == '+' || num[0] == '-')
	{
		if (ft_strlen(num) > ft_strlen("+9223372036854775807"))
			return (0);
		if (num[0] == '+' && ft_strncmp(num, "+9223372036854775807", 20) > 0)
			return (0);
		if (num[0] == '-' && ft_strncmp(num, "-9223372036854775808", 20) > 0)
			return (0);
	}
	else
	{
		if (ft_strlen(num) > ft_strlen("9223372036854775807"))
			return (0);
		if (ft_strncmp(num, "9223372036854775807", 19) > 0)
			return (0);
	}
	return (1);
}

int	check_nb(char *num)
{
	int	i;

	i = 0;
	if (num[0] == '-' || num[0] == '+')
		i++;
	while (num[i])
	{
		if (num[i] < '0' || num[i] > '9')
			return (0);
		i++;
	}
	if (check_long_long(num) == 0)
		return (0);
	return (1);
}

void	exit_cmd(char **cmd)
{
	long long	nb;

	if (!cmd[1])
		exit(g_ret);
	if (check_nb(cmd[1]) == 0)
	{
		printf("exit: %s: numeric argument required\n", cmd[1]);
		exit(2);
	}
	if (cmd[2])
	{
		printf("exit: too many arguments\n");
		return ;
	}
	nb = ft_atoi_exit(cmd[1]);
	if (nb < 0)
		exit((unsigned int)nb % 256);
	else if (nb > 255)
		exit(nb % 256);
	else
		exit(nb);
}
