/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 19:33:47 by aseptimu          #+#    #+#             */
/*   Updated: 2022/03/27 12:58:09 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../includes/builtin.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	int		lens1;
	int		lens2;

	if (!s1 && !s2)
		return ((void *)0);
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return (ft_strdup(s1));
	lens1 = ft_strlen((char *)s1);
	lens2 = ft_strlen((char *)s2);
	p = (char *)malloc((lens1 + lens2 + 1) * sizeof(char));
	if (!p)
		ft_malloc_error();
	ft_memcpy(p, s1, lens1);
	ft_memcpy(&p[lens1], s2, lens2);
	p[lens1 + lens2] = '\0';
	return (p);
}
