/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseptimu <aseptimu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 12:14:10 by aseptimu          #+#    #+#             */
/*   Updated: 2022/03/27 12:14:33 by aseptimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"

static void	ft_add_export(t_env *tmp, char *arg)
{
	char	*fre;

	fre = tmp->arg;
	tmp->arg = ft_strjoin(tmp->arg, arg);
	if (!tmp->arg)
		ft_malloc_error();
	free(fre);
}

static void	no_plus_realloc(char **args)
{
	char	*tmp;

	tmp = *args;
	while (*tmp && *tmp != '+')
		tmp++;
	ft_strlcpy(tmp, tmp + 1, ft_strlen(*args));
}

void	export_add(t_env **env, char *args)
{
	t_env	*tmp;
	char	*var;
	char	*name;

	name = ft_substr(args, 0, ft_strnotcharlen(args, '+'));
	if (!name)
		ft_malloc_error();
	var = ft_strchr(args, '=');
	var++;
	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, name, \
			(ft_strlen(name) + ft_strlen(tmp->name))))
		{
			ft_add_export(tmp, var);
			free(name);
			return ;
		}
		tmp = tmp->next;
	}
	free(name);
	no_plus_realloc(&args);
	*env = env_add_node(*env, new_env(args));
}
