/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseptimu <aseptimu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 13:43:27 by aseptimu          #+#    #+#             */
/*   Updated: 2022/03/22 18:40:44 by aseptimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "builtin.h"

static void	child_process(t_node *node, t_fd *fd, char ***envp, int ecode)
{
	int	built;

	close(fd->pip_fd[0]);
	close(fd->std_in_out[0]);
	close(fd->std_in_out[1]);
	built = isbuiltin(node->args);
	if (built == -1)
		exe(node->args, *envp);
	else
		exit(builtin(node->args, built, envp, ecode));
}

static int	make_process(t_node *node, t_fd *fd, char ***envp, int ecode)
{
	if (pipe(fd->pip_fd) == -1)
		return (ft_sys_errors("minishell: pipe"));
	dup2(fd->pip_fd[1], 1);
	close(fd->pip_fd[1]);
	if (redirector(node->redir, fd->std_in_out) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	fd->pid = fork();
	if (fd->pid == -1)
		return (ft_sys_errors("minishell: fork"));
	if (fd->pid == 0)
		child_process(node, fd, envp, ecode);
	dup2(fd->std_in_out[1], 1);
	if (node->pipe == 1)
		dup2(fd->pip_fd[0], 0);
	close(fd->pip_fd[0]);
	return (0);
}

static int	last_cmd(t_node *node, t_fd *fd, char ***envp, int ecode)
{
	int	built;

	built = isbuiltin(node->args);
	fd->pid = fork();
	if (fd->pid == -1)
		return (ft_sys_errors("minishell: fork"));
	if (fd->pid == 0)
	{
		if (redirector(node->redir, fd->std_in_out) == EXIT_FAILURE)
			exit (EXIT_FAILURE);
		close(fd->std_in_out[0]);
		close(fd->std_in_out[1]);
		if (built == -1)
			exe(node->args, *envp);
		else
			exit(builtin(node->args, built, envp, ecode));
	}
	return (0);
}

int	forker(t_node *node, t_fd *fd, char ***envp, int ecode)
{
	while (node->pipe != false)
	{
		if (make_process(node, fd, envp, ecode) == 1)
		{
			dup2(fd->std_in_out[0], 0);
			waiter(fd);
			return (128);
		}
		node = node->next;
	}
	if (last_cmd(node, fd, envp, ecode) == 1)
	{
		dup2(fd->std_in_out[0], 0);
		waiter(fd);
		return (128);
	}
	dup2(fd->std_in_out[0], 0);
	fd->code = waiter(fd);
	return (fd->code);
}
