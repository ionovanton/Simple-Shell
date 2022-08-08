/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 01:19:17 by srobt             #+#    #+#             */
/*   Updated: 2022/03/29 02:03:42 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	lex_cond_token(char c)
{
	return (ft_issep(c) || ft_isredir(c) || c == '&');
}

static void	check(long long *i, char **string, t_lexer *l)
{
	*string = dict((void *)(*i), string_dict, get_value);
	if (!ft_strncmp(l->optr, *string, ((*i) % 2) + 1))
	{
		lex_strjoin(&l->nptr, dict((void *)(*i), token_dict, get_value));
		ft_moveptr(&l->optr, ((*i) % 2) + 1);
		if (*i >= TOKEN_GREATGREAT && *i <= TOKEN_LESS)
		{
			ft_skip_space(&l->optr);
			lex_extended_quotes(l);
		}
	}
}

void	lex_add_token(t_lexer *l)
{
	char		*string;
	long long	i;

	while (*l->optr && lex_cond_token(*l->optr))
	{
		if (ft_isspace(*l->optr))
		{
			lex_strjoin(&l->nptr, T_SPACE);
			ft_skip_space(&l->optr);
		}
		i = 1;
		while (i < TOKEN_LIST_LENGTH && lex_cond_token(*l->optr))
		{
			check(&i, &string, l);
			i++;
		}
	}
}
