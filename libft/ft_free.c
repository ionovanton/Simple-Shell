/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 19:32:54 by srobt             #+#    #+#             */
/*   Updated: 2022/03/27 12:06:29 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_string(char **s)
{
	if (!(*s))
		return ;
	free(*s);
	*s = NULL;
}

void	ft_free_array(char ***a)
{
	int	i;

	i = 0;
	if (!(*a))
		return ;
	while ((*a)[i])
		ft_free_string(&(*a)[i++]);
	free(*a);
	*a = NULL;
}
