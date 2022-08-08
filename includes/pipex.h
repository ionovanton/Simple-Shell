/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseptimu <aseptimu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 19:07:43 by aseptimu          #+#    #+#             */
/*   Updated: 2022/03/22 19:07:43 by aseptimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include "minishell.h"

typedef struct s_fd
{
	int		pip_fd[2];
	int		std_in_out[2];
	pid_t	pid;
	pid_t	last_pid;
	int		code;
	int		status;
}				t_fd;

typedef struct s_heredoc
{
	pid_t	pid;
	int		fd;
	int		status;
	int		word_len;
	char	tmp_buf[2];
	char	*buf_msg;
	char	*msg;
	int		msg_len;
	char	*tmp;
}				t_heredoc;

void	exe(char **args, char **envp);
int		waiter(t_fd *fd);
int		pipex(t_node *node, char ***envp, int ecode);
int		forker(t_node *node, t_fd *fd, char ***envp, int ecode);
int		redirector(t_redir *redir, int std_in_out[2]);
int		err_redir(char *msg, char *perr);
int		here_doc(char *word, int std_in_out[2]);
int		ft_sys_errors(char *error);
#endif
