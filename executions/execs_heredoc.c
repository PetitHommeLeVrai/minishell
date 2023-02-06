/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <aboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:14:06 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/06 12:05:08 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tmp.h"

void	here_doc(char *argv, t_cmd_line *cmd_line)
{
	int		file;
	char	*buf;

	file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (file == -1)
		msg_error("FAILED TO CREATE HEREDOC\n");
	while (1)
	{
		buf = readline("> ");
		if (!ft_strncmp(argv, buf, ft_strlen(argv) + 1))
			break ;
		write(file, buf, ft_strlen(buf));
		write(file, "\n", 1);
		free(buf);
	}
	free(buf);
	close(file);
	cmd_line->infile = open(".heredoc_tmp", O_RDONLY);
	if (cmd_line->infile == -1)
	{
		unlink(".heredoc_tmp");
		msg_error("FAILED TO OPEN HEREDOC");
	}
}
