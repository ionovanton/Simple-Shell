/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 20:32:36 by srobt             #+#    #+#             */
/*   Updated: 2022/03/29 05:06:37 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pat_fill_rest(char *s, char *p, t_matrix *m)
{
	int	i;
	int	j;

	i = 1;
	while (i < m->h)
	{
		j = 1;
		while (j < m->w)
		{
			if (p[i] == ASTERISK)
				m->mat[i][j] = (m->mat[i][j - 1] || m->mat[i - 1][j]);
			else
				m->mat[i][j] = (m->mat[i - 1][j - 1] && p[i] == s[j]);
			j++;
		}
		i++;
	}
}

static int	pat_fill(char *s, char *p, t_matrix *m)
{
	int	i;

	i = 0;
	m->mat[0][i++] = T;
	while (i < m->w)
		m->mat[0][i++] = F;
	i = 1;
	while (i < m->h)
	{
		if (p[i] == ASTERISK)
			m->mat[i][0] = m->mat[i - 1][0];
		else
			m->mat[i][0] = F;
		i++;
	}
	pat_fill_rest(s, p, m);
	return (m->mat[m->h - 1][m->w - 1]);
}

static int	pat_asterisk_check(char *p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		if (p[i] != ASTERISK)
			return (false);
		i++;
	}
	return (true);
}

int	pattern(char *s, char *p)
{
	t_matrix	*m;
	char		*str;
	char		*pat;
	int			result;

	if (pat_asterisk_check(p))
		return (true);
	str = pat_convert_string(s);
	pat = pat_convert_string(p);
	pat_init_matrix(ft_strlen(str), ft_strlen(pat), &m);
	result = pat_fill(str, pat, m);
	ft_free_string(&str);
	ft_free_string(&pat);
	pat_destroy_matrix(&m);
	return (result);
}
