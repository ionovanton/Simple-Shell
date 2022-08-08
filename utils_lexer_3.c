/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 19:45:57 by srobt             #+#    #+#             */
/*   Updated: 2022/03/29 05:05:00 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lex_init(int exit_status, char **s, char ***envp, t_lexer **l)
{
	(*l) = malloc(sizeof(t_lexer));
	if (!(*l))
		return (false);
	(*l)->envp = *envp;
	(*l)->ecode = exit_status;
	(*l)->nptr = (char *)ft_calloc(1, sizeof(char));
	if (!(*l)->nptr)
	{
		free(*l);
		return (false);
	}
	(*l)->sep = 0;
	(*l)->optr = *s;
	return (true);
}

void	lex_destroy(t_lexer **l)
{
	free(*l);
	*l = NULL;
}

int	lex_check_environ(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == C_ENV && (ft_issysname(s[i + 1]) || s[i + 1] == C_ECODE))
			return (true);
		i++;
	}
	return (false);
}

char	*lex_env_getkey(char *s)
{
	char	*key;

	if (*s == C_ECODE)
		key = ft_strdup(S_ECODE);
	else if (ft_isdigit(*s))
		key = ft_ctoa(*s);
	else
		key = ft_strcdup(s, ft_isnotsysname);
	if (!key)
		sh_exit(FAIL);
	return (key);
}

void	lex_pattern_matching(char **s)
{
	char	**filenames;
	char	**good;
	int		i;

	filenames = pat_get_filenames();
	if (!filenames)
		sh_exit(FAIL);
	good = NULL;
	i = 0;
	while (filenames[i])
	{
		if (pattern(filenames[i], *s) && filenames[i][0] != '.')
			good = ft_arradd(&good, filenames[i]);
		i++;
	}
	if (good)
	{
		ft_free_string(s);
		*s = ft_arrtostr(good, T_SPACE);
	}
	ft_free_array(&good);
	ft_free_array(&filenames);
}
