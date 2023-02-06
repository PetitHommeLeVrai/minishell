/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <aboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 10:43:38 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/06 12:13:20 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tmp.h"

void	infile(t_token *word, t_cmd_line *cmd_line)
{
	if (cmd_line->infile)
		close(cmd_line->infile);
	cmd_line->infile = open(word->word, O_RDONLY);
	if (cmd_line->infile == -1)
	{
		perror(word->word);
		exit(2);
	}
}

void	outfile(t_token *word, t_cmd_line *cmd_line)
{
	if (cmd_line->outfile)
		close(cmd_line->outfile);
	cmd_line->outfile = open(word->word, O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (cmd_line->outfile == -1)
	{
		perror(word->word);
		exit(2);
	}
}

void	outfileover(t_token *word, t_cmd_line *line)
{
	if (line->outfile)
		close(line->outfile);
	line->outfile = open(word->word, O_WRONLY | O_CREAT | O_APPEND, 0000644);
	if (line->outfile == -1)
	{
		perror(word->word);
		exit(2);
	}
}

void	get_files(t_exec *exec, t_cmd_line *cmd_line)
{
	while (cmd_line->word != NULL)
	{
		if (cmd_line->word->type == INFILE)
			infile(cmd_line->word, cmd_line);
		else if (cmd_line->word->type == OUTFILE)
			outfile(cmd_line->word, cmd_line);
		else if (cmd_line->word == OUTFILEOVER)
			outfileover(cmd_line->word, cmd_line);
		else if (cmd_line->word == LIMITOR)
		{
			if (cmd_line->infile)
				close(cmd_line->infile);
			heredoc(cmd_line->word->word, exec);
		}
		cmd_line->word = cmd_line->word->next;
	}
}
