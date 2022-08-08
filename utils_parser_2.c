/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 02:25:21 by srobt             #+#    #+#             */
/*   Updated: 2022/03/29 04:19:28 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	par_strjoin(char **str, char *word)
{
	char	*tmp;

	if (!word)
		return ;
	tmp = *str;
	*str = ft_strjoin(tmp, word);
	ft_free_string(&tmp);
	if (!(*str))
		sh_exit(FAIL);
}

char	*par_get_token(char *s)
{
	char	*ptr;
	char	*token;
	int		i;

	ptr = s;
	ft_skip_to_cond(&ptr, ft_isredir);
	if (!(*ptr))
		return (ft_strdup(""));
	i = 0;
	while (ptr[i] && ptr[i] != '>')
		i++;
	i++;
	token = ft_strndup(ptr, i);
	return (token);
}

static void	last_quote(char **token, int *sep_status, long long *status)
{
	*sep_status = true;
	par_strjoin(token, T_SEP);
	*status &= ~(1 << TOKEN_SPACE);
	*status &= ~(1 << TOKEN_BQ);
}

static void	first_quote(char **token, long long *status)
{
	par_strjoin(token, T_SEP);
	*status &= ~(1 << TOKEN_SPACE);
	*status &= ~(1 << TOKEN_AQ);
}

char	*par_get_compressed_token(\
long long status, char **token_word, int *isstart)
{
	char	*token;
	int		sep_status;

	token = NULL;
	sep_status = false;
	if (status & (1 << TOKEN_BQ) && (*isstart) == false)
		last_quote(&token, &sep_status, &status);
	if (status & 0b1111000)
	{
		if (sep_status == false && *isstart == false)
		{
			status &= ~(1 << TOKEN_SPACE);
			par_strjoin(&token, T_SEP);
		}
		par_strjoin(&token, (char *)dict((void *)(long long)ft_getpow2(\
		status & 120), token_dict, get_value));
		par_strjoin(&token, *token_word);
	}
	if (status & (1 << TOKEN_AQ) && (*isstart) == false)
		first_quote(&token, &status);
	if (status & (1 << TOKEN_SPACE))
		par_strjoin(&token, T_SEP);
	*isstart = false;
	ft_free_string(token_word);
	return (token);
}
