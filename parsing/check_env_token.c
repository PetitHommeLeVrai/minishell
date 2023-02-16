/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 21:15:10 by ychun             #+#    #+#             */
/*   Updated: 2023/02/16 16:27:23 by ychun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_token_have_env(char *word)
{
	int	i;

	i = -1;
	while (word[++i])
	{
		if (word[i] == '$')
		{
			if (word[i + 1] == '\0' || word[i + 1] == '$')
				return (i);
			if (ft_isalpha(word[i + 1]) || word[i + 1] == '_'
				|| word[i + 1] == '?')
				return (i);
		}
	}
	return (-1);
}

int	find_tail_dollar(char *word, int i)
{
	if (word[i] == '?')
		return (i);
	while (word[i])
	{
		if (ft_isalpha(word[i]) || word[i] == '_' || ft_isdigit(word[i]))
			i++;
		else
			break ;
	}
	return (i - 1);
}

char	*ft_strjoin_word(char *word, char *value, char *head, char *tail)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (head[++j])
		word[++i] = head[j];
	j = -1;
	while (value[++j])
		word[++i] = value[j];
	j = -1;
	while (tail[++j])
		word[++i] = tail[j];
	i++;
	word[i] = '\0';
	free(head);
	free(tail);
	return (word);
}

char	*get_new_word(t_token **token, t_env_list *env, int head, int tail)
{
	char	*key;
	char	*value;
	char	*new_word;

	key = ft_substr((*token)->word, head + 1, tail - head);
	value = find_value_by_key(env, key, token);
	new_word = (char *)malloc(sizeof(char)
			* (ft_strlen((*token)->word)
				- (tail - head) + ft_strlen(value) + 1));
	if (!new_word)
		ft_error("Allocation error", STDERR_FILENO);
	ft_strjoin_word(new_word, value, ft_substr((*token)->word, 0, head),
		ft_substr((*token)->word, tail + 1, ft_strlen((*token)->word)));
	free(key);
	free(value);
	if (!ft_strcmp((*token)->word, "$?"))
	{
		free(new_word);
		new_word = ft_itoa(g_ret);
	}
	return (new_word);
}

void	check_env_token(t_token_list *tokens, t_env_list *env)
{
	int		i;
	int		head_dollar;

	i = -1;
	while (tokens->token[++i].type != T_NULL)
	{
		if (tokens->token[i].type != T_SINGLE_QUOTES)
		{
			head_dollar = check_token_have_env(tokens->token[i].word);
			if (head_dollar != -1)
				get_new_dollar(&tokens->token[i], head_dollar, env);
			if (tokens->token[i].type != T_DOUBLE_QUOTES && head_dollar != -1)
				tokens = re_get_token_list(tokens, tokens->token[i].word, i);
		}
	}
}
