/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseptimu <aseptimu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:45:36 by aseptimu          #+#    #+#             */
/*   Updated: 2022/03/02 12:45:36 by aseptimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

int	err_redir(char *msg, char *perr)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	perror(perr);
	return (EXIT_FAILURE);
}

static int	check_redir(t_redir *redir, int fd_redir, \
			int std_in_out[2], int ecode)
{
	if (redir->token == TOKEN_GREAT)
	{
		fd_redir = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_redir == -1)
			return (err_redir("minishell: ", redir->filename));
		dup2(fd_redir, STDOUT_FILENO);
	}
	else if (redir->token == TOKEN_LESS)
	{
		fd_redir = open(redir->filename, O_RDONLY);
		if (fd_redir == -1)
			return (err_redir("minishell: ", redir->filename));
		dup2(fd_redir, STDIN_FILENO);
	}
	else if (redir->token == TOKEN_LESSLESS)
		ecode = here_doc(redir->filename, std_in_out);
	else if (redir->token == TOKEN_GREATGREAT)
	{
		fd_redir = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd_redir == -1)
			return (err_redir("minishell: ", redir->filename));
		dup2(fd_redir, STDOUT_FILENO);
	}
	return (ecode);
}

int	redirector(t_redir *redir, int std_in_out[2])
{
	int	fd_redir;
	int	ecode;

	ecode = 0;
	fd_redir = 0;
	if (redir == NULL)
		return (0);
	while (redir != NULL)
	{
		if (check_redir(redir, fd_redir, std_in_out, ecode) != 0)
			return (EXIT_FAILURE);
		redir = redir->next;
	}
	return (0);
}
