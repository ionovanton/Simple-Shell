/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:29:15 by srobt             #+#    #+#             */
/*   Updated: 2022/03/29 00:38:45 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_get_envp(char *key, char **envp)
{
	const int	length = ft_strlen(key);
	int			i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(key, envp[i], length))
			return (ft_strdup(envp[i] + length + 1));
		i++;
	}
	return (NULL);
}
