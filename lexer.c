/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 19:35:35 by srobt             #+#    #+#             */
/*   Updated: 2022/04/02 17:39:12 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	lex_make_string(t_lexer *l)
{
	int	status;

	ft_skip_space(&l->optr);
	status = 0;
	while (*l->optr)
	{
		lex_add_quote(l);
		lex_add_word(l);
		lex_add_token(l);
	}
	status = lex_error_check(l);
	return (status);
}

void	lexer(char **s, t_sh *sh)
{
	t_lexer	*l;
	int		status;

	lex_init(sh->exit_status, s, &sh->envp, &l);
	if (!l)
		sh_exit(FAIL);
	status = lex_make_string(l);
	if (status == 2)
	{
		sh->exit_status = status;
		free(sh->head);
		sh->head = NULL;
		ft_putstr_fd("minishell: syntax error\n", 2);
		ft_free_string(&l->nptr);
		ft_free_string(s);
		lex_destroy(&l);
	}
	else
	{
		ft_free_string(s);
		*s = l->nptr;
		lex_destroy(&l);
	}
}
