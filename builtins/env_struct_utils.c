/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_struct_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseptimu <aseptimu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:27:12 by aseptimu          #+#    #+#             */
/*   Updated: 2022/03/12 17:58:51 by aseptimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"

t_env	*env_add_node(t_env *env, t_env *new)
{
	t_env	*tmp;

	if (!env)
		return (new);
	tmp = env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (env);
}

static int	new_env_init(t_env *new, char *arg)
{
	new->arg = NULL;
	new->name = NULL;
	new->next = NULL;
	new->name = ft_substr(arg, 0, ft_strnotcharlen(arg, '='));
	if (!new->name)
	{
		free(new);
		return (1);
	}
	return (0);
}

t_env	*new_env(char *arg)
{
	t_env	*new;
	char	*var;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	if (new_env_init(new, arg) == 1)
		return (NULL);
	var = ft_strchr(arg, '=');
	if (var != NULL)
	{
		var++;
		new->arg = ft_strdup(var);
		if (!new->arg)
		{
			free(new->name);
			free(new);
			return (NULL);
		}
	}
	return (new);
}

int	env_lstsize(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

void	env_node_del(t_env **env, char *name)
{
	t_env	*tmp;
	t_env	*free_env;

	free_env = *env;
	tmp = *env;
	while (free_env)
	{
		if (ft_strncmp(free_env->name, name, ft_strlen(free_env->name)) == 0)
		{
			if (free_env == *env)
				*env = (*env)->next;
			else
			{
				while (tmp->next != free_env)
					tmp = tmp->next;
				tmp->next = free_env->next;
			}
			free(free_env->name);
			free(free_env->arg);
			free(free_env);
			return ;
		}
		free_env = free_env->next;
	}
}
