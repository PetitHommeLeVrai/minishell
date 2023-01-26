/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <aboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:57:50 by aboyer            #+#    #+#             */
/*   Updated: 2023/01/26 17:16:10 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int export(char *var, t_env *env)
{
	while (env->next != NULL)
		env = env->next;
	env->next = malloc(sizeof(t_env));
	if (env->next == NULL)
		return (0);
	env->next->begin = env->begin;
	env->next->var = ft_strdup(var);
	env->next->next = NULL;
}
