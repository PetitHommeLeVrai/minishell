/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <aboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:10:42 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/01 14:40:05 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tmp.h"

void	infile(t_exec *exec, t_token *word)
{
	if (exec->infile)
		close(exec->infile);
	exec->infile = open(word->word, O_RDONLY);
	if (exec->infile == -1)
	{
		perror(word->word);
		exit(2);
	}
}

void	outfile(t_exec *exec, t_token *word)
{
	if (exec->outfile)
		close(exec->outfile);
	exec->outfile = open(word->word, O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (exec->outfile == -1)
	{
		perror(word->word);
		exit(2);
	}
}

void	outfileover(t_exec *exec, t_token *word)
{
	if (exec->outfile)
		close(exec->outfile);
	exec->outfile = open(word->word, O_WRONLY | O_CREAT | O_APPEND, 0000644);
	if (exec->outfile == -1)
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
			infile(exec, cmd_line->word);
		else if (cmd_line->word->type == OUTFILE)
			outfile(exec, cmd_line->word);
		else if (cmd_line->word == OUTFILEOVER)
			outfileover(exec, cmd_line->word);
		else if (cmd_line->word == LIMITOR)
		{
			if (exec->infile)
				close(exec->infile);
			heredoc(cmd_line->word->word, exec);
		}
		cmd_line->word = cmd_line->word->next;
	}
}

void	child(t_exec exec, t_cmd_line *cmd_line, t_env_list *env)
{
	exec.pid = fork();
	if (!exec.pid)
	{
		get_files(&exec, cmd_line);
	}
}
