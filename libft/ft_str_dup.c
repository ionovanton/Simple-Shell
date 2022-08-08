/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_dup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseptimu <aseptimu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:15:00 by srobt             #+#    #+#             */
/*   Updated: 2022/03/31 14:49:30 by aseptimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcdup(const char *s, int (*f)(char))
{
	char	*dup;
	int		n;
	int		i;

	i = 0;
	while (!(*f)(s[i]) && s[i])
		i++;
	n = i;
	dup = malloc(sizeof(char) * (n + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strndup(const char *s, int n)
{
	char	*dup;
	int		i;

	dup = malloc(sizeof(char) * (n + 1));
	if (dup == NULL)
		exit (1);
	i = 0;
	while (i < n)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	**ft_arrdup(char **a)
{
	const int	size = ft_arrlen(a);
	char		**new;
	int			i;

	i = 0;
	new = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new)
		return (NULL);
	while (a[i])
	{
		new[i] = ft_strdup(a[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}
