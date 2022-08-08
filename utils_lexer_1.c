/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseptimu <aseptimu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:27:17 by srobt             #+#    #+#             */
/*   Updated: 2022/03/31 16:32:43 by aseptimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_env_value(t_enve *e, char **envp, int ecode)
{
	if (ft_isdigit(*e->key))
	{
		if (*e->key == '0')
			e->value = ft_strdup("minishell");
		else
			e->value = ft_strdup("");
	}
	else
		lex_copyenv(&e->key, &e->value, envp, ecode);
}

static int	loop(t_enve *e, char **envp, int ecode)
{
	while (*e->optr)
	{
		while (*e->optr && *e->optr == C_ENV \
		&& (*(e->optr + 1) == C_ECODE || ft_issysname(*(e->optr + 1))))
		{
			e->key = lex_env_getkey(++e->optr);
			get_env_value(e, envp, ecode);
			if (!e->key || !e->value)
				return (false);
			ft_moveptr(&e->optr, ft_strlen(e->key));
			if (e->value)
			{
				lex_paste_word(&e->nptr, e->value);
				ft_free_string(&e->value);
			}
			ft_free_string(&e->key);
		}
		if (!(*e->optr))
			break ;
		*e->nptr++ = *e->optr++;
	}
	return (true);
}

int	lex_env_expand(char **s, char **envp, int ecode)
{
	t_enve	e;

	if (!lex_check_environ(*s))
		return (true);
	e.n = lex_env_get_newlength(*s, envp, ecode);
	if (e.n == 0)
	{
		ft_free_string(s);
		return (true);
	}
	e.new_str = (char *)malloc(sizeof(char) * (e.n + 1));
	if (!e.new_str)
		sh_exit(FAIL);
	e.optr = *s;
	e.nptr = e.new_str;
	if (!loop(&e, envp, ecode))
		sh_exit(FAIL);
	*e.nptr = '\0';
	ft_free_string(s);
	*s = e.new_str;
	return (true);
}
