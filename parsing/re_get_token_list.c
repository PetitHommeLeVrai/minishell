/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_get_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:37:01 by ychun             #+#    #+#             */
/*   Updated: 2023/02/13 15:41:15 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_new_dollar(t_token token, int head_dollar, t_env_list *env)
{
	int		tail_dollar;
	char	*new_word;

	tail_dollar = find_tail_dollar(token.word,
			head_dollar + 1);
	new_word = get_new_word(&token,
			env, head_dollar, tail_dollar);
	token.origin = ft_strdup(token.word);
	free(token.word);
	token.word = new_word;
}

t_token_list	*re_get_token_list(t_token_list *tokens)
{
	t_token_list	*new_token_list;
	char			*tmp;
	char			*new_cmd;
	int				i;

	i = -1;
	while (tokens->token[++i].type != T_NULL)
	{
		while (tokens->token[i].word)
		{
			tmp = (char *)malloc(sizeof(char)
					* ft_strlen(tokens->token[i].word));
			if (!tmp)
				ft_error("Allocation Error", STDERR_FILENO);
			tmp = tokens->token[i].word;
			new_cmd = ft_strjoin(new_cmd, tmp);
		}
		new_cmd[ft_strlen(new_cmd)] = ' ';
		new_cmd[ft_strlen(new_cmd) + 1] = '\0';
	}
	ft_free_token_list(tokens);
	new_token_list = (t_token_list *)malloc(sizeof(t_token_list));
	if (init_token_list(new_cmd, new_token_list))
		return (NULL);
	return (new_token_list);
}
