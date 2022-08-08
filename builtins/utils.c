/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:08:41 by aseptimu          #+#    #+#             */
/*   Updated: 2022/03/21 17:39:49 by aseptimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin.h"
#include <stdio.h>

void	ft_malloc_error(void)
{
	perror("minishell: malloc");
	exit(EXIT_FAILURE);
}

int	ft_cd_errors(char *putstr, char *perr, int code)
{
	ft_putstr_fd(putstr, STDERR_FILENO);
	perror(perr);
	return (code);
}

char	**free_envp(char ***envp)
{
	int	i;

	if (!*envp)
		return (NULL);
	i = 0;
	while ((*envp)[i])
	{
		free((*envp)[i]);
		i++;
	}
	free(*envp);
	*envp = NULL;
	return (NULL);
}

int	ft_strnotcharlen(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
		i++;
	return (i);
}

char	*take_env_var(t_env *env, char *var)
{
	if (env == NULL || var == NULL)
		return (NULL);
	while (env && env->name != var)
	{
		if (ft_strncmp(env->name, var, ft_strlen(var) + 1) == 0)
			return (env->arg);
		env = env->next;
	}
	return (NULL);
}
