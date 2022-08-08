/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:28:15 by srobt             #+#    #+#             */
/*   Updated: 2022/03/19 01:45:50 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_skip_space(char **s)
{
	while ((**s) && ft_isspace(**s))
		(*s)++;
}

int	ft_skip_to_cond(char **s, int (*f)(char))
{
	int	i;

	i = 0;
	while (!(*f)(**s) && (**s))
	{
		(*s)++;
		i++;
	}
	return (i);
}
