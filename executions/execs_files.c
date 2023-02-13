/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <aboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 10:43:38 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/13 12:28:40 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	infile(char *word, t_cmd_line *cmd_line)
{
	if (cmd_line->infile >= 0)
		close(cmd_line->infile);
	cmd_line->infile = open(word, O_RDONLY);
	if (cmd_line->infile == -1)
	{
		perror(word);
		exit(2);
	}
}

void	outfile(char *word, t_cmd_line *cmd_line)
{
	if (cmd_line->outfile >= 0)
		close(cmd_line->outfile);
	cmd_line->outfile = open(word, O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (cmd_line->outfile == -1)
	{
		perror(word);
		exit(2);
	}
}

void	outfileover(char *word, t_cmd_line *line)
{
	if (line->outfile >= 0)
		close(line->outfile);
	line->outfile = open(word, O_WRONLY | O_CREAT | O_APPEND, 0000644);
	if (line->outfile == -1)
	{
		perror(word);
		exit(2);
	}
}

void	get_files(t_exec *exec, t_cmd_line *cmd_line)
{
	int	i;

	i = 0;
	(void)exec;
	while (i < cmd_line->token_count)
	{
		if (cmd_line->token[i].type == INFILE)
			infile(cmd_line->token[i].word, cmd_line);
		else if (cmd_line->token[i].type == OUTFILE)
			outfile(cmd_line->token[i].word, cmd_line);
		else if (cmd_line->token[i].type == OUTFILEOVER)
			outfileover(cmd_line->token[i].word, cmd_line);
		else if (cmd_line->token[i].type == LIMITOR)
		{
			if (cmd_line->infile >= 0)
				close(cmd_line->infile);
			here_doc(cmd_line->token[i].word, cmd_line);
		}
		i++;
	}
}
