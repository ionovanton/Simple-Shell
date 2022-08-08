/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 15:38:30 by aseptimu          #+#    #+#             */
/*   Updated: 2022/03/14 12:44:24 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

static void	*free_words(char ***a, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free((*a)[i]);
		(*a)[i] = NULL;
		i++;
	}
	free(*a);
	(*a) = NULL;
	return (NULL);
}

static int	count_words(const char *s, char c)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] == 0)
			break ;
		n++;
		while (s[i] != c && s[i])
			i++;
	}
	return (n);
}

static void	*parse_words(const char *s, char c, char ***a)
{
	int	shift;
	int	i;
	int	j;

	shift = 0;
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] == 0)
			break ;
		shift = i;
		while (s[i] != c && s[i])
			i++;
		(*a)[j] = NULL;
		(*a)[j] = ft_strndup(s + shift, i - shift);
		if (!(*a)[j])
			return (free_words(a, j - 1));
		j++;
	}
	(*a)[j] = NULL;
	return ((void *)1);
}

char	**ft_split(const char *s, char c)
{
	char	**a;

	a = NULL;
	a = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!a)
		return (NULL);
	if (!parse_words(s, c, &a))
		return (NULL);
	return (a);
}
