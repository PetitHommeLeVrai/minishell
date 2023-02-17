/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_get_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:37:01 by ychun             #+#    #+#             */
/*   Updated: 2023/02/16 21:27:05 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_new_dollar(t_token *token, int head_dollar, t_env_list *env)
{
	int		tail_dollar;
	char	*new_word;

	tail_dollar = find_tail_dollar(token->word,
			head_dollar + 1);
	new_word = get_new_word(&token,
			env, head_dollar, tail_dollar);
	token->origin = ft_strdup(token->word);
	free(token->word);
	token->word = new_word;
}

void	token_copy(t_token *token, t_token *new_token, int idx, char **word)
{
	int	j;
	int	k;
	int	l;

	j = -1;
	k = -1;
	l = -1;
	while (++j < idx)
		new_token[j] = token[j];
	while (word[++k])
	{
		new_token[++j].word = ft_strdup(word[k]);
		if (!new_token[j].word)
			ft_error("Allocation Error", STDERR_FILENO);
		new_token[j].type = T_WORD;
		new_token[j].flag_env = 1;
	}
	while (token[++idx].type != T_NULL)
		new_token[++j] = token[idx];
	while (word[++l])
		free(word[l]);
	free(word);
}

t_token_list	*re_get_token_list(t_token_list *tokens, char *word, int idx)
{
	t_token_list	*new_token_list;
	char			**split;
	int				i;

	i = -1;
	if (ft_strcmp(word, " "))
		return (tokens);
	new_token_list = (t_token_list *)malloc(sizeof(t_token_list));
	if (!new_token_list)
		ft_error("Allocation Error", STDERR_FILENO);
	split = ft_split(word, ' ');
	if (!split)
		ft_error("Allocation Error", STDERR_FILENO);
	while (split[++i])
		i++;
	new_token_list->token = (t_token *)malloc(sizeof(t_token)
			* (tokens->count + i + 1));
	if (!new_token_list->token)
		ft_error("Allocation Error", STDERR_FILENO);
	init_tokens(new_token_list, tokens->count + i);
	new_token_list->count = tokens->count + i;
	token_copy(tokens->token, new_token_list->token, idx, split);
	ft_free_token_list(tokens);
	return (new_token_list);
}
