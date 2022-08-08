/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseptimu <aseptimu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 03:07:45 by srobt             #+#    #+#             */
/*   Updated: 2022/03/31 15:25:09 by aseptimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lex_env_get_length(char *key)
{
	int	i;

	i = 0;
	if (!key)
		return (0);
	while (key[i] && key[i] != '=')
		i++;
	return (i);
}

char	*lex_getenv(char *key, char **envp)
{
	while (*envp && ft_strncmp(key, *envp, lex_env_get_length(*envp)))
		envp++;
	if (*envp)
		return (*envp + lex_env_get_length(*envp) + 1);
	else
		return (NULL);
}

void	lex_copyenv(char **key, char **value, char **envp, int ecode)
{
	char	*ptr;

	if (!ft_strncmp(*key, S_ECODE, 1))
	{
		(*value) = ft_itoa(ecode);
		return ;
	}
	ptr = lex_getenv(*key, envp);
	if (ptr)
		(*value) = ft_strdup(ptr);
	else
		(*value) = ft_strdup("");
	if (!value)
		sh_exit(FAIL);
}

void	lex_paste_word(char **s, char *word)
{
	while (*word)
	{
		**s = *word;
		(*s)++;
		word++;
	}
}

void	lex_strjoin(char **str, char *word)
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
