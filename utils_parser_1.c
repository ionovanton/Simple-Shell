/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 14:06:35 by srobt             #+#    #+#             */
/*   Updated: 2022/03/29 03:22:47 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	moveptr(char **s, char **ptr, int shift, int sep_length)
{
	ft_moveptr(s, shift);
	ft_moveptr(s, sep_length);
	ft_moveptr(ptr, sep_length);
}

static void	find(char **ptr, char *sep, int *shift, int sep_length)
{
	*shift = 0;
	while (**ptr && ft_strncmp(*ptr, sep, sep_length))
	{
		(*ptr)++;
		(*shift)++;
	}
}

static int	parse_words(char *s, char *sep, char ***a)
{
	const int	sep_length = ft_strlen(sep);
	char		*ptr;
	int			shift;
	int			i;

	i = 0;
	ptr = s;
	while (*ptr)
	{
		find(&ptr, sep, &shift, sep_length);
		(*a)[i] = ft_strndup(s, shift);
		if (!(*a)[i])
		{
			ft_free_array(a);
			return (false);
		}
		moveptr(&s, &ptr, shift, sep_length);
		i++;
	}
	(*a)[i] = NULL;
	return (true);
}

static int	count_words(char *s, char *sep)
{
	const int	sep_length = ft_strlen(sep);
	int			n;

	n = 0;
	while (*s)
	{
		while (*s && ft_strncmp(s, sep, sep_length))
			s++;
		n++;
		ft_moveptr(&s, sep_length);
	}
	return (n);
}

char	**par_split(char *s, char *sep)
{
	const int	n = count_words(s, sep);
	char		**a;

	a = (char **)malloc(sizeof(char *) * (n + 1));
	if (!a)
		return (NULL);
	if (!parse_words(s, sep, &a))
		return (NULL);
	return (a);
}
