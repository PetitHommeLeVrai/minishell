/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychun <ychun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 21:15:10 by ychun             #+#    #+#             */
/*   Updated: 2023/02/06 01:34:02 by ychun            ###   ########.fr       */
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
		i++;
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

char	*get_new_word(t_token *token, t_env_list *env, int head, int tail)
{
	char	*key;
	char	*value;
	char	*new_word;

	key = ft_substr(token->word, head + 1, tail - head);
	//if (key == "?")
		//value of exit code
	value = find_value_by_key(env, key, &token);
	new_word = (char *)malloc(sizeof(char)
			* (ft_strlen(token->word) - (tail - head) + ft_strlen(value) + 1));
	if (!new_word)
		ft_error("Allocation error", STDERR_FILENO);
	ft_strjoin_word(new_word, value, ft_substr(token->word, 0, head),
		ft_substr(token->word, tail + 1, ft_strlen(token->word)));
	free(key);
	free(value);
	return (new_word);
}

void	check_env_token(t_token_list *tokens, t_env_list *env)
{
	int		i;
	int		head_dollar;
	int		tail_dollar;
	char	*new_word;

	i = -1;
	while (tokens->count > ++i)
	{
		if (tokens->token[i].type != T_SINGLE_QUOTES && tokens->token[i].word != NULL)
		{
			head_dollar = check_token_have_env(tokens->token[i].word);
			if (head_dollar != -1)
			{
				tail_dollar = find_tail_dollar(tokens->token[i].word,
						head_dollar + 1);
				new_word = get_new_word(&tokens->token[i],
						env, head_dollar, tail_dollar);
				tokens->token[i].origin = ft_strdup(tokens->token[i].word);
				free(tokens->token[i].word);
				tokens->token[i].word = new_word;
			}
		}
	}
}
