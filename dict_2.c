/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 02:10:18 by srobt             #+#    #+#             */
/*   Updated: 2022/03/29 02:10:53 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**string_dict(int n)
{
	static char	**dict;

	if (!dict)
	{
		dict = (char **)malloc(sizeof(char *) * (n + 1));
		if (!dict)
			return (NULL);
		dict[TOKEN_NONE] = ft_strdup(NONE);
		dict[TOKEN_OR] = ft_strdup(S_OR);
		dict[TOKEN_PIPE] = ft_strdup(S_PIPE);
		dict[TOKEN_GREATGREAT] = ft_strdup(S_GREATGREAT);
		dict[TOKEN_GREAT] = ft_strdup(S_GREAT);
		dict[TOKEN_LESSLESS] = ft_strdup(S_LESSLESS);
		dict[TOKEN_LESS] = ft_strdup(S_LESS);
		dict[TOKEN_AND] = ft_strdup(S_AND);
		dict[TOKEN_BEFORE] = ft_strdup(S_BEFORE);
		dict[TOKEN_SPACE] = ft_strdup(NONE);
		dict[TOKEN_SEP] = ft_strdup(NONE);
		dict[TOKEN_AQ] = ft_strdup(NONE);
		dict[TOKEN_BQ] = ft_strdup(NONE);
		dict[n] = NULL;
		if (!dict_check_integrity(dict, n))
			return (NULL);
	}
	return (dict);
}

char	**token_dict(int n)
{
	static char	**dict;

	if (!dict)
	{
		dict = (char **)malloc(sizeof(char *) * (n + 1));
		if (!dict)
			return (NULL);
		dict[TOKEN_NONE] = ft_strdup(NONE);
		dict[TOKEN_OR] = ft_strdup(T_OR);
		dict[TOKEN_PIPE] = ft_strdup(T_PIPE);
		dict[TOKEN_GREATGREAT] = ft_strdup(T_GREATGREAT);
		dict[TOKEN_GREAT] = ft_strdup(T_GREAT);
		dict[TOKEN_LESSLESS] = ft_strdup(T_LESSLESS);
		dict[TOKEN_LESS] = ft_strdup(T_LESS);
		dict[TOKEN_AND] = ft_strdup(T_AND);
		dict[TOKEN_BEFORE] = ft_strdup(S_BEFORE);
		dict[TOKEN_SEP] = ft_strdup(T_SEP);
		dict[TOKEN_SPACE] = ft_strdup(T_SPACE);
		dict[TOKEN_AQ] = ft_strdup(T_AQ);
		dict[TOKEN_BQ] = ft_strdup(T_BQ);
		dict[n] = NULL;
		if (!dict_check_integrity(dict, n))
			return (NULL);
	}
	return (dict);
}

int	free_dict(char **dict, int n)
{
	int	i;

	i = 0;
	if (!dict)
		return (false);
	while (i < n)
		ft_free_string(&dict[i++]);
	free(dict);
	dict = NULL;
	return (false);
}

int	dict_check_integrity(char **dict, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (!dict[i++])
			return (free_dict(dict, n));
	}
	return (true);
}

void	dict_destroy(char **(*f)(int))
{
	char	**dict_ptr;

	dict_ptr = (*f)(TOKEN_LIST_LENGTH);
	free_dict(dict_ptr, TOKEN_LIST_LENGTH);
}
