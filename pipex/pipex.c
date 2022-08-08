/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseptimu <aseptimu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:57:33 by aseptimu          #+#    #+#             */
/*   Updated: 2022/03/27 13:25:57 by aseptimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include "builtin.h"

int	ft_sys_errors(char *error)
{
	perror(error);
	return (EXIT_FAILURE);
}

int	waiter(t_fd *fd)
{
	fd->last_pid = fd->pid;
	while (fd->pid > 0)
	{
		fd->pid = wait(&fd->code);
		if (fd->pid == fd->last_pid)
			fd->status = fd->code;
	}
	if (WIFSIGNALED(fd->status))
		return (128 + WTERMSIG(fd->status));
	return (WEXITSTATUS(fd->status));
}

static int	sys_cmd(t_node *node, t_fd *fd, char ***envp)
{
	if (redirector(node->redir, fd->std_in_out) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	fd->pid = fork();
	if (fd->pid == -1)
		return (ft_sys_errors("minishell: fork"));
	else if (fd->pid == 0)
	{
		close(fd->std_in_out[0]);
		close(fd->std_in_out[1]);
		exe(node->args, *envp);
	}
	fd->code = waiter(fd);
	return (fd->code);
}

static int	one_cmd(t_node *node, t_fd *fd, char ***envp, int ecode)
{
	int		built;

	built = isbuiltin(node->args);
	if (built != -1)
	{
		if (redirector(node->redir, fd->std_in_out) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		fd->code = builtin(node->args, built, envp, ecode);
	}
	else
		fd->code = sys_cmd(node, fd, envp);
	return (fd->code);
}

int	pipex(t_node *node, char ***envp, int ecode)
{
	t_fd	fd;

	fd.std_in_out[0] = dup(STDIN_FILENO);
	fd.std_in_out[1] = dup(STDOUT_FILENO);
	if (node == NULL)
		return (0);
	if (node->pipe == 0)
		fd.code = one_cmd(node, &fd, envp, ecode);
	else
		fd.code = forker(node, &fd, envp, ecode);
	dup2(fd.std_in_out[0], 0);
	dup2(fd.std_in_out[1], 1);
	close(fd.std_in_out[0]);
	close(fd.std_in_out[1]);
	unlink("/tmp/tmpfile_hdoc");
	return (fd.code);
}
