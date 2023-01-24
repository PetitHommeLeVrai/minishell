/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:37:15 by aboyer            #+#    #+#             */
/*   Updated: 2023/01/24 01:03:17 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(void)
{
	char	*str;

	while (1)
	{
		str = readline("$> ");
		if (str)
		{
//			if (str[0] != 0)
//			{

//			}
		}
		else
		{
			printf("exit\n");
			break ;
		}
		free(str);
		str = NULL;
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	prompt();
}
