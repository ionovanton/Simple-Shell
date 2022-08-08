/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 01:18:19 by srobt             #+#    #+#             */
/*   Updated: 2022/03/29 05:04:05 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lex_add_word(t_lexer *l)
{
	char	*tmp;
	int		trigger_asterisk;
	int		i;

	trigger_asterisk = false;
	tmp = NULL;
	i = 0;
	while ((l->optr)[i] && !ft_issep((l->optr)[i]) && !ft_isredir((l->optr)[i]) \
	&& !ft_isquote((l->optr)[i]) && (l->optr)[i] != '&')
	{
		if ((l->optr)[i] == ASTERISK)
			trigger_asterisk = true;
		i++;
	}
	if (i == 0)
		return ;
	tmp = ft_strndup(l->optr, i);
	if (trigger_asterisk)
		lex_pattern_matching(&tmp);
	lex_env_expand(&tmp, l->envp, l->ecode);
	ft_moveptr(&l->optr, i);
	lex_strjoin(&l->nptr, tmp);
	ft_free_string(&tmp);
	lex_extended_quotes(l);
}
