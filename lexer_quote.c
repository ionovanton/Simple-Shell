/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseptimu <aseptimu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 01:19:51 by srobt             #+#    #+#             */
/*   Updated: 2022/03/31 15:29:15 by aseptimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	quote_close_func(int i, char **tmp, t_lexer *l)
{
	ft_moveptr(&l->optr, i + 1);
	lex_strjoin(&l->nptr, *tmp);
	ft_free_string(tmp);
	lex_extended_quotes(l);
	lex_strjoin(&l->nptr, T_BQ);
}

static void	quote_open_func(int *i, char *q, char **tmp, t_lexer *l)
{
	*q = *l->optr;
	ft_moveptr(&l->optr, 1);
	*tmp = NULL;
	*i = 0;
	lex_strjoin(&l->nptr, T_AQ);
}

void	lex_add_quote(t_lexer *l)
{
	char	*tmp;
	char	q;
	int		i;

	if (!ft_isquote(*l->optr))
		return ;
	quote_open_func(&i, &q, &tmp, l);
	while ((l->optr)[i] && (l->optr)[i] != q)
		i++;
	if (i == 0)
	{
		if (*l->optr == q)
			l->optr++;
		lex_extended_quotes(l);
		lex_strjoin(&l->nptr, T_BQ);
		return ;
	}
	tmp = ft_strndup(l->optr, i);
	if (!tmp)
		sh_exit(FAIL);
	if (q == C_DQ)
		lex_env_expand(&tmp, l->envp, l->ecode);
	quote_close_func(i, &tmp, l);
}

void	lex_extended_quotes(t_lexer *l)
{
	char	*tmp;
	char	q;
	int		i;

	i = 0;
	while (ft_isquote(*l->optr))
	{
		q = *l->optr;
		i = 0;
		l->optr++;
		while ((l->optr)[i] != q)
			i++;
		if (i != 0)
		{
			tmp = ft_strndup(l->optr, i);
			if (q == C_DQ)
				lex_env_expand(&tmp, l->envp, l->ecode);
			ft_moveptr(&l->optr, i);
			lex_strjoin(&l->nptr, tmp);
			ft_free_string(&tmp);
			l->optr++;
		}
		else
			l->optr++;
	}
}
