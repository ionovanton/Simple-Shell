/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseptimu <aseptimu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 04:33:17 by srobt             #+#    #+#             */
/*   Updated: 2022/03/31 15:37:00 by aseptimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	par_copy_word(char **new_str, char **s, int *isstart)
{
	char	*ptr;
	char	*tmp;
	int		n;

	tmp = NULL;
	ptr = *s;
	n = 0;
	while (*ptr && !par_is_token(ptr))
		n += ft_moveptr(&ptr, 1);
	if (n == 0)
		return ;
	*isstart = false;
	tmp = ft_strndup(*s, n);
	ft_moveptr(s, n);
	par_strjoin(new_str, tmp);
	ft_free_string(&tmp);
}

void	par_insert_new_token(char **new_str, char **ptr, int *isstart)
{
	char		*token_word;
	char		*tmp;
	const int	status = par_get_status(ptr, &token_word);

	if (status == 0)
		return ;
	tmp = par_get_compressed_token(status, &token_word, isstart);
	par_strjoin(new_str, tmp);
	ft_free_string(&tmp);
}

void	par_compress_tokens(char ***args)
{
	char	*new_str;
	char	*ptr;
	int		isstart;
	int		i;

	i = 0;
	while ((*args)[i])
	{
		new_str = ft_calloc(1, sizeof(char));
		if (!new_str)
			sh_exit(FAIL);
		isstart = true;
		ptr = (*args)[i];
		par_skip_token(&ptr, T_SPACE, 9);
		while (*ptr)
		{
			par_copy_word(&new_str, &ptr, &isstart);
			par_insert_new_token(&new_str, &ptr, &isstart);
		}
		ft_free_string(&(*args)[i]);
		(*args)[i++] = new_str;
	}
}
