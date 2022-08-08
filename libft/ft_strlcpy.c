/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 19:17:20 by aseptimu          #+#    #+#             */
/*   Updated: 2022/03/27 12:00:48 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[j])
		j++;
	if (dstsize == 0)
		return (j);
	while (dstsize - 1)
	{
		dst[i] = src[i];
		if (src[i] == 0 || dst[i] == 0)
			return (j);
		i++;
		dstsize--;
	}
	dst[i] = '\0';
	return (j);
}

size_t	ft_strcpy(char *dst, const char *src)
{
	const char	*s;
	char		*d;
	size_t		i;

	s = src;
	d = dst;
	i = 0;
	while (*s)
	{
		*d++ = *s++;
		i++;
	}
	return (i);
}
