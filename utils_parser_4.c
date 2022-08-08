/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseptimu <aseptimu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 04:19:50 by srobt             #+#    #+#             */
/*   Updated: 2022/03/31 15:31:31 by aseptimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	par_is_token(char *ptr)
{
	char		*dict_ptr;
	long long	i;

	i = 1;
	while (*ptr && i < TOKEN_LIST_LENGTH)
	{
		dict_ptr = (void *)dict((void *)i, token_dict, get_value);
		if (!ft_strncmp(ptr, dict_ptr, ft_strlen(dict_ptr)))
			return (true);
		i++;
		if (i == TOKEN_PIPE || i == TOKEN_BEFORE || i == TOKEN_SEP)
			i++;
	}
	return (false);
}

// Return '1' if any real token is present in the string 's'.
int	par_check_token_presence(char *s, char *token, int token_length)
{
	int	status;

	status = false;
	if (!ft_strncmp(token, ANY, token_length))
	{
		token = par_get_token(s);
		if (!token)
			return (-1);
		if (dict(token, token_dict, get_key))
			status = true;
		ft_free_string(&token);
		return (status);
	}
	return (status);
}

// No defence against non-tokens.
int	par_skip_token_once(char **ptr)
{
	int	n;

	n = 0;
	if (**ptr)
	{
		(*ptr)++;
		n++;
	}
	n += ft_skip_to_cond(ptr, ft_isredir) + 2;
	if (**ptr)
	{
		(*ptr)++;
		n++;
	}
	return (n);
}

int	par_skip_token(char **ptr, char *token, int token_length)
{
	int	n;

	n = 0;
	if (!ft_strncmp(token, ANY, token_length))
	{
		while (**ptr && par_is_token(*ptr))
			par_skip_token_once(ptr);
		return (n);
	}
	while (**ptr && !ft_strncmp(*ptr, token, token_length))
		n += ft_moveptr(ptr, token_length);
	return (n);
}
