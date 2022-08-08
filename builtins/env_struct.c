/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:24:11 by aseptimu          #+#    #+#             */
/*   Updated: 2022/03/25 19:35:28 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"

void	free_env_struct(t_env **env)
{
	t_env	*tmp;

	if (!*env)
		return ;
	while (*env)
	{
		tmp = *env;
		free((*env)->name);
		free((*env)->arg);
		(*env) = (*env)->next;
		free(tmp);
	}
	*env = NULL;
}

t_env	*get_env_struct(char **envp)
{
	t_env	*env;
	t_env	*new;
	int		i;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		new = new_env(envp[i]);
		if (!new)
		{
			free_env_struct(&env);
			return (NULL);
		}
		env = env_add_node(env, new);
		i++;
	}
	return (env);
}

static char	*restore(t_env *env, char **envp, int i)
{
	char	*tmp;

	if (env->arg != NULL)
	{
		envp[i] = ft_strjoin(env->name, "=");
		if (!envp[i])
			return (NULL);
		tmp = envp[i];
		envp[i] = ft_strjoin(envp[i], env->arg);
		free(tmp);
		if (!envp[i])
			return (NULL);
	}
	else
	{
		envp[i] = ft_strdup(env->name);
		if (!envp[i])
			return (NULL);
	}
	return (envp[i]);
}

char	**restore_envp(t_env *env)
{
	char	**envp;
	int		i;

	envp = (char **)malloc(sizeof(char *) * (env_lstsize(env) + 1));
	if (!envp)
		ft_malloc_error();
	i = 0;
	while (env)
	{
		envp[i] = restore(env, envp, i);
		if (!envp[i])
		{
			free_envp(&envp);
			ft_malloc_error();
		}
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
