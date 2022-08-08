/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseptimu <aseptimu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:09:51 by aseptimu          #+#    #+#             */
/*   Updated: 2022/03/31 14:42:06 by aseptimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <stdio.h>
#include "libft.h"
#include <errno.h>

static int	go_home(t_env *env)
{
	char	*home;

	home = take_env_var(env, "HOME");
	if (home == NULL)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
		return (1);
	}
	chdir(home);
	return (0);
}

static void	change_oldpwd(t_env *env, char *old_pwd)
{
	t_env	*tmp;

	tmp = env;
	while (tmp && ft_strncmp(tmp->name, "OLDPWD", 6) != 0)
		tmp = tmp->next;
	if (tmp == NULL)
	{
		tmp = new_env("OLDPWD");
		if (!tmp)
			ft_malloc_error();
		tmp->arg = ft_strdup(old_pwd);
		if (!tmp->arg)
			ft_malloc_error();
		env_add_node(env, tmp);
	}
	else
	{
		free(tmp->arg);
		tmp->arg = ft_strdup(old_pwd);
		if (!tmp->arg)
			ft_malloc_error();
	}
}

static void	change_pwd(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp && (ft_strncmp(tmp->name, "PWD", 4) != 0))
		tmp = tmp->next;
	if (tmp == NULL)
	{
		tmp = new_env("PWD");
		if (!tmp)
			ft_malloc_error();
		tmp->arg = getcwd(NULL, 0);
		if (!tmp->arg && errno == ENOMEM)
			exit(1);
		env_add_node(env, tmp);
	}
	else
	{
		free(tmp->arg);
		tmp->arg = getcwd(NULL, 0);
		if (!tmp->arg && errno == ENOMEM)
			exit(1);
	}
}

int	go_back(t_env *env)
{
	char	*go_back;
	char	*curdir;

	go_back = take_env_var(env, "OLDPWD");
	if (go_back == NULL)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
		return (1);
	}
	chdir(go_back);
	curdir = getcwd(NULL, 0);
	if (!curdir && errno == ENOMEM)
		exit(1);
	ft_putstr_fd(curdir, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	free(curdir);
	return (0);
}

int	cd(char **path, t_env *env)
{
	char	*pwd;
	int		code;

	code = 0;
	pwd = getcwd(NULL, 0);
	if (path[1] == NULL)
		code = go_home(env);
	else if (ft_strncmp(path[1], "-", 2) == 0)
		code = go_back(env);
	else
	{
		if (chdir(path[1]) == -1)
		{
			free(pwd);
			return (ft_cd_errors("minishell: cd: ", path[1], 1));
		}
	}
	if (!pwd)
		return (ft_cd_errors("cd: error retrieving current directory:", \
				" getcwd: cannot access parent directories", 0));
	change_pwd(env);
	change_oldpwd(env, pwd);
	free(pwd);
	return (code);
}
