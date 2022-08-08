/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseptimu <aseptimu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 14:14:22 by aseptimu          #+#    #+#             */
/*   Updated: 2022/03/31 14:15:04 by aseptimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

static int	set_level(int lvl, t_env **env, t_env **tmp)
{
	if (*tmp == NULL)
	{
		*tmp = new_env("SHLVL");
		if (!*tmp)
			ft_malloc_error();
		*env = env_add_node(*env, *tmp);
		lvl = 1;
		return (lvl);
	}
	else
	{
		lvl = get_lvl((*tmp)->arg);
		if (lvl < 0)
			lvl = -1;
		lvl++;
		free((*tmp)->arg);
		return (lvl);
	}	
}

static t_env	*adjust_shell_level(t_env *env)
{
	t_env	*tmp;
	int		lvl;

	lvl = 0;
	tmp = env;
	while (tmp && ft_strncmp(tmp->name, "SHLVL", 5))
		tmp = tmp->next;
	lvl = set_level(lvl, &env, &tmp);
	if (lvl > 1000)
	{
		printf \
		("minishell: warning: shell level (%d) too high, resetting to 1\n", lvl);
		lvl = 1;
	}
	if (lvl != 1000)
		tmp->arg = ft_itoa(lvl);
	else
	{
		tmp->arg = ft_strdup("\0");
		if (!tmp->arg)
			ft_malloc_error();
	}
	return (env);
}

static void	set_pwd(t_env **tmp, t_env **env)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		ft_malloc_error();
	*tmp = new_env("PWD");
	if (!*tmp)
		ft_malloc_error();
	(*tmp)->arg = pwd;
	*env = env_add_node(*env, *tmp);
}

static t_env	*check_pwd_oldpwd(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp && ft_strncmp(tmp->name, "PWD", 4))
		tmp = tmp->next;
	if (tmp == NULL)
		set_pwd(&tmp, &env);
	tmp = env;
	while (tmp && ft_strncmp(tmp->name, "OLDPWD", 7))
		tmp = tmp->next;
	if (tmp == NULL)
	{
		tmp = new_env("OLDPWD");
		if (!tmp)
			ft_malloc_error();
		env = env_add_node(env, tmp);
	}
	return (env);
}

int	check_env(char ***envp)
{
	t_env	*env;

	env = get_env_struct(*envp);
	if (!env)
		return (0);
	adjust_shell_level(env);
	check_pwd_oldpwd(env);
	free_envp(envp);
	*envp = restore_envp(env);
	if (!*envp)
		return (0);
	free_env_struct(&env);
	return (1);
}
