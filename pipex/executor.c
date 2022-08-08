/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 13:15:05 by aseptimu          #+#    #+#             */
/*   Updated: 2022/03/20 15:41:06 by aseptimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

void	error_exit(char *message, int errorcode)
{
	ft_putstr_fd("minishell: ", 2);
	perror(message);
	exit(errorcode);
}

void	free_split(char **string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		free(string[i]);
		i++;
	}
	free(string);
}

char	*full_path(char *paths, char **cmdargs, char **path)
{
	char	**tmp;
	char	*cmd;

	tmp = path;
	while (*path)
	{
		paths = ft_strjoin(*path, "/");
		if (!paths)
			error_exit("malloc", 1);
		cmd = ft_strjoin(paths, cmdargs[0]);
		if (!cmd)
			error_exit("malloc", 1);
		if (access(cmd, F_OK) == 0)
		{		
			free_split(tmp);
			free(paths);
			return (cmd);
		}
		free(paths);
		free(cmd);
		path++;
	}
	free_split(tmp);
	return (NULL);
}

char	*get_path(char **cmdargs, char **envp)
{
	char	*paths;
	char	**path;

	while (*envp)
	{
		if (!ft_strncmp(*envp, "PATH=", 5))
		{
			paths = ft_strchr(*envp, '=');
			break ;
		}
		envp++;
	}
	if (*envp == NULL)
	{
		paths = ft_strjoin("./", cmdargs[0]);
		if (!paths)
			error_exit("malloc", 1);
		return (paths);
	}
	paths++;
	path = ft_split(paths, ':');
	if (!path)
		error_exit("malloc", 1);
	return (full_path(paths, cmdargs, path));
}

void	exe(char **args, char **envp)
{
	char	*cmd;

	if (!(args[0][0] == '/' \
		|| (args[0][0] == '.' && (args[0][1] == '.' || args[0][1] == '/'))))
	{
		cmd = get_path(args, envp);
		if (cmd == NULL)
			error_exit(args[0], 127);
	}
	else
	{
		cmd = ft_strdup(args[0]);
		if (!cmd)
			error_exit("malloc", EXIT_FAILURE);
	}
	if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == -1)
		error_exit(cmd, 126);
	if (execve(cmd, args, envp) == -1)
		error_exit(cmd, 127);
}
