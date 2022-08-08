/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseptimu <aseptimu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 01:22:19 by srobt             #+#    #+#             */
/*   Updated: 2022/03/31 15:33:09 by aseptimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	key_check(char **ptr, long long *key)
{
	if (*key == 2)
	{
		while (**ptr && !ft_strncmp(*ptr, T_SPACE, 9))
			par_skip_token_once(ptr);
		if (**ptr == '\0' || !ft_strncmp(*ptr, T_PIPE, 8))
			return (false);
	}
	else if (*key >= 3 && *key <= 6)
	{
		*key = (long long)dict(*ptr, token_dict, get_key);
		if (**ptr == '\0' || (*key >= 2 && *key <= 6))
			return (false);
	}
	return (true);
}

static int	check(char *ptr)
{
	long long	key;

	key = 0;
	if (!ft_strncmp(ptr, T_PIPE, 8))
		return (false);
	while (*ptr)
	{
		while (*ptr)
		{
			key = (long long)dict(ptr, token_dict, get_key);
			if (key >= 2 && key <= 6)
			{
				par_skip_token_once(&ptr);
				break ;
			}	
			ptr++;
		}
		if (!key_check(&ptr, &key))
			return (false);
	}
	return (true);
}

int	lex_error_check(t_lexer *l)
{
	char	*ptr;

	ptr = l->nptr;
	if (!par_check_token_presence(ptr, ANY, 3))
		return (0);
	if (!check(ptr))
		return (2);
	return (0);
}
