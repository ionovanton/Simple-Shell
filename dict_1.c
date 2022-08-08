/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 14:24:14 by srobt             #+#    #+#             */
/*   Updated: 2022/03/29 02:10:47 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*get_value(void *data, char **dict)
{
	const long long	key = (long long)data;

	return (dict[key]);
}

void	*get_key(void *data, char **dict)
{
	const char	*value = (char *)data;
	long long	i;

	i = 0;
	while (i < TOKEN_LIST_LENGTH)
	{
		if (!ft_strncmp(dict[i], value, ft_strlen(dict[i])))
			return ((void *)i);
		i++;
	}
	return ((void *)0);
}

// Access key/value based dictionaries: string_dict or token_dict
void	*dict(void *data, char **(*g)(int), void *(*f)(void *, char **))
{
	char	**dict;

	dict = (*g)(TOKEN_LIST_LENGTH);
	if (!dict)
		return (NULL);
	return ((*f)(data, dict));
}
