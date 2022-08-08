/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 03:48:40 by srobt             #+#    #+#             */
/*   Updated: 2022/03/29 04:11:25 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	till_word(char **ptr, int *status)
{
	const int	a = !ft_strncmp(*ptr, T_AQ, 6);
	const int	b = par_is_token(*ptr);

	if (a || !b)
	{
		*status |= 1 << (long long)dict((void *)(*ptr), token_dict, get_key);
		par_skip_token_once(ptr);
		return (true);
	}
	return (false);
}

static int	till_quote(char **ptr, int *status)
{
	const int	a = !ft_strncmp(*ptr, T_BQ, 6);

	(void)(*status);
	if (a)
		return (true);
	return (false);
}

static void	par_skip_word(char **ptr, char **token_word)
{
	char	*p;
	int		i;

	p = *ptr;
	i = 0;
	while (*p && !par_is_token(p))
	{
		p++;
		i++;
	}
	if (i == 0)
		*token_word = NULL;
	else
		*token_word = ft_strndup(*ptr, i);
	ft_moveptr(ptr, i);
}

static int	control(char **ptr, char **token_word, \
int *status, int (**f)(char **, int *))
{
	*token_word = NULL;
	*status = 0;
	if (par_is_token(*ptr))
	{
		if (!ft_strncmp(*ptr, T_AQ, 6))
			*f = till_quote;
		else
			*f = till_word;
		return (true);
	}
	return (false);
}

// Get bitmask status of token series. Function works inplace.
int	par_get_status(char **ptr, char **token_word)
{
	int		status;
	int		index;
	int		(*f)(char **, int *);

	if (!control(ptr, token_word, &status, &f))
		return (0);
	while (**ptr && par_is_token(*ptr))
	{
		if (f(ptr, &status))
			break ;
		index = (long long)dict((void *)(*ptr), token_dict, get_key);
		status |= 1 << index;
		par_skip_token_once(ptr);
		if (index >= TOKEN_GREATGREAT && index <= TOKEN_LESS)
		{
			par_skip_word(ptr, token_word);
			break ;
		}
	}
	return (status);
}
