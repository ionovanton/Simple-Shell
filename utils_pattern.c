/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pattern.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseptimu <aseptimu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:13:56 by srobt             #+#    #+#             */
/*   Updated: 2022/03/31 16:32:21 by aseptimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*pat_convert_string(char *s)
{
	const int	length = ft_strlen(s) + 1;
	char		*new;
	int			i;

	new = malloc(sizeof(char) * (length + 1));
	if (!new)
		return (NULL);
	i = 0;
	new[i++] = E;
	while (i < length)
	{
		new[i] = s[i - 1];
		i++;
	}
	new[i] = '\0';
	return (new);
}

int	pat_destroy_matrix(t_matrix **m)
{
	int	i;

	i = 0;
	while (i < (*m)->h)
	{
		free((*m)->mat[i]);
		(*m)->mat[i] = NULL;
		i++;
	}
	free((*m)->mat);
	(*m)->mat = NULL;
	free(*m);
	*m = NULL;
	return (false);
}

static int	init(int w, int h, t_matrix **m)
{
	(*m)->h = h;
	(*m)->w = w;
	(*m)->mat = (int **)malloc(sizeof(int *) * h);
	if (!(*m)->mat)
		return (false);
	return (true);
}

int	pat_init_matrix(int w, int h, t_matrix **m)
{
	int	i;
	int	j;

	*m = malloc(sizeof(t_matrix));
	if (!(*m))
		return (false);
	if (!init(w, h, m))
		return (false);
	i = 0;
	while (i < h)
	{
		(*m)->mat[i++] = (int *)malloc(sizeof(int) * w);
		if (!(*m)->mat[i - 1])
			return (pat_destroy_matrix(m));
	}
	i = 0;
	while (i < (*m)->h)
	{
		j = 0;
		while (j < (*m)->w)
			(*m)->mat[i][j++] = N;
		i++;
	}
	return (true);
}

char	**pat_get_filenames(void)
{
	DIR				*d;
	struct dirent	*dir;
	char			**filenames;

	filenames = NULL;
	d = opendir(".");
	dir = readdir(d);
	filenames = ft_arradd(&filenames, dir->d_name);
	if (!filenames)
		return (NULL);
	while (dir)
	{
		dir = readdir(d);
		if (!dir)
			break ;
		filenames = ft_arradd(&filenames, dir->d_name);
		if (!filenames)
			return (NULL);
	}
	closedir(d);
	return (filenames);
}
