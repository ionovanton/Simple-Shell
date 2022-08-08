/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseptimu <aseptimu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:51:17 by aseptimu          #+#    #+#             */
/*   Updated: 2022/03/21 17:39:34 by aseptimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"

int	ft_env(char **argc, char **envp)
{
	int	i;

	(void)argc;
	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
		{
			ft_putstr_fd(envp[i], 1);
			ft_putchar_fd('\n', 1);
		}
		i++;
	}
	return (0);
}
