/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arradd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 19:30:01 by srobt             #+#    #+#             */
/*   Updated: 2022/03/29 00:38:37 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Add string to two-dim array
char	**ft_arradd(char ***a, char *s)
{
	const int	old_length = ft_arrlen(*a);
	char		**new;
	int			i;

	new = (char **)malloc(sizeof(char *) * (old_length + 1 + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (i < old_length)
	{
		new[i] = (*a)[i];
		i++;
	}
	new[i++] = ft_strdup(s);
	if (!new[i - 1])
	{
		ft_free_array(&new);
		return (NULL);
	}
	new[i] = NULL;
	free(*a);
	*a = NULL;
	return (new);
}

static char	*init(int *length, int delim_length, int *arr_length, char **a)
{
	char	*s;
	int		i;

	i = 0;
	*length = 0;
	while (a[i])
		*length += ft_strlen(a[i++]);
	*arr_length = i;
	s = ft_calloc((*length) + ((*arr_length) - 1) \
	* delim_length + 1, sizeof(char));
	return (s);
}

char	*ft_arrtostr(char **a, char *delim)
{
	int		arr_length;
	int		length;
	char	*s;
	char	*ptr;
	int		n;

	s = init(&length, ft_strlen(delim), &arr_length, a);
	if (!s)
		return (NULL);
	ptr = s;
	while (*a)
	{
		n = ft_strcpy(ptr, *a);
		ft_moveptr(&ptr, n);
		if (--arr_length)
		{
			n = ft_strcpy(ptr, delim);
			ft_moveptr(&ptr, n);
		}
		a++;
	}
	*ptr = 0;
	return (s);
}
