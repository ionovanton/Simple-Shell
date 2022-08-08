/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 19:48:52 by srobt             #+#    #+#             */
/*   Updated: 2022/03/29 02:54:17 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_int(t_enve *e, char **s)
{
	char	*ptr;

	ptr = *s;
	ptr++;
	if (*ptr == '0')
		e->value = ft_strndup("minishell", 9);
	else
		e->value = ft_strdup("");
	if (e->value == NULL)
		sh_exit(FAIL);
	e->n += ft_strlen(e->value);
	ft_moveptr(s, 2);
	ft_free_string(&e->value);
}

static void	get_exit(t_enve *e, char **s, int ecode)
{
	(*s)++;
	e->key = lex_env_getkey(*s);
	e->value = ft_itoa(ecode);
	if (!e->key || !e->value)
		sh_exit(FAIL);
	e->n += ft_strlen(e->value);
	ft_moveptr(s, 1);
	ft_free_string(&e->value);
	ft_free_string(&e->key);
}

static void	get_rest(t_enve *e, char **s, char **envp)
{
	(*s)++;
	e->key = lex_env_getkey(*s);
	if (!e->key)
		sh_exit(FAIL);
	e->n += ft_strlen(lex_getenv(e->key, envp));
	ft_moveptr(s, ft_strlen(e->key));
	ft_free_string(&e->key);
}

int	lex_env_get_newlength(char *s, char **envp, int ecode)
{
	t_enve	e;

	e.key = NULL;
	e.n = 0;
	while (*s)
	{
		while (*s && *s == C_ENV && (*(s + 1) == C_ECODE \
		|| ft_issysname(*(s + 1))))
		{
			if (*s == C_ENV && *(s + 1) == C_ECODE)
				get_exit(&e, &s, ecode);
			else if (*s == C_ENV && ft_isdigit(*(s + 1)))
				get_int(&e, &s);
			else
				get_rest(&e, &s, envp);
		}
		if (!(*s))
			return (e.n);
		s++;
		e.n++;
	}
	return (e.n);
}
