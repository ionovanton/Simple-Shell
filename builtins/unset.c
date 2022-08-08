/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:51:27 by aseptimu          #+#    #+#             */
/*   Updated: 2022/03/27 19:16:06 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"

static int	check_input(char *args)
{
	int	i;

	if (!(ft_isalpha(args[0]) || args[0] == '_'))
		return (-1);
	i = 0;
	while (args[i])
	{
		if (!(ft_isalnum(args[i]) || args[i] == '_'))
			return (-1);
		i++;
	}
	return (0);
}

int	ft_unset(char **args, t_env **env)
{
	int	i;
	int	code;

	i = 1;
	code = EXIT_SUCCESS;
	while (args[i])
	{
		if (check_input(args[i]) == 0)
			env_node_del(env, args[i]);
		else
		{
			ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
			ft_putstr_fd(args[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			code = EXIT_FAILURE;
		}
		i++;
	}
	return (code);
}
