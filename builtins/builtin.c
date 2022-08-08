/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:46:32 by aseptimu          #+#    #+#             */
/*   Updated: 2022/03/27 18:58:46 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "typedef.h"
#include "builtin.h"
#include "libft.h"

int	isbuiltin(char **args)
{
	if (args == NULL)
		return (0);
	if (!ft_strncmp(args[0], "echo", 5))
		return (1);
	if (!ft_strncmp(args[0], "pwd", 4))
		return (2);
	if (!ft_strncmp(args[0], "cd", 3))
		return (3);
	if (!ft_strncmp(args[0], "export", 7))
		return (4);
	if (!ft_strncmp(args[0], "unset", 6))
		return (5);
	if (!ft_strncmp(args[0], "env", 4))
		return (6);
	if (!ft_strncmp(args[0], "exit", 5))
		return (7);
	return (-1);
}

static int	fcking_norm(int code, char **args, t_env *env, int flag)
{
	if (flag == 1)
		code = echo(args);
	if (flag == 2)
		code = pwd();
	if (flag == 3)
		code = cd(args, env);
	return (code);
}

int	builtin(char **args, int flag, char ***envp, int ecode)
{
	t_env	*env;
	int		code;

	code = 0;
	if (flag != -1)
	{
		env = get_env_struct(*envp);
		if (!env)
			ft_malloc_error();
		code = fcking_norm(code, args, env, flag);
		if (flag == 4)
			code = ft_export(args, &env);
		if (flag == 5)
			code = ft_unset(args, &env);
		if (flag == 6)
			code = ft_env(args, *envp);
		if (flag == 7)
			ft_exit(ecode, args);
		free_envp(envp);
		*envp = restore_envp(env);
		free_env_struct(&env);
		return (code);
	}
	return (-1);
}
