/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <aboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:07:32 by aboyer            #+#    #+#             */
/*   Updated: 2023/02/01 14:39:49 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TMP_H
# define TMP_H

# include <fcntl.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum s_enum
{
	NON,
	ARG,
	INFILE_CHAR,
	OUTFILE_CHAR,
	HEREDOC_CHAR,
	OUTFILEOVER_CHAR,
	INFILE,
	OUTFILE,
	LIMITOR,
	OUTFILEOVER
}						t_enum;

typedef struct s_token
{
	char				*word;
	t_enum				type;
	struct s_token		*next;
}						t_token;

typedef struct s_cmd_line
{
	char				*cmd;
	struct s_token		*word;
	struct cmd_line		*next;
}						t_cmd_line;

typedef struct s_exec
{
	int					infile;
	int					outfile;
	char				**cmd_paths;
	char				*cmd;
	char				**cmd_args;
	pid_t				pid;
	int					*pipe;
	int					id;
}						t_exec;

typedef struct s_cmd_list
{
	struct s_cmd		*head;
	struct s_cmd		*tail;
}						t_cmd_list;

typedef struct s_env_list
{
	char				*var;
	struct s_env_list	*next;
}						t_env_list;

#endif
