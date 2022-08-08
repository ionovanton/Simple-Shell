/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 17:16:35 by srobt             #+#    #+#             */
/*   Updated: 2022/03/13 17:20:05 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_remove_word(char **s, char *word)
{
	const int	word_length = ft_strlen(word);
	char		*ptr;
	char		*new_string;

	ptr = *s;
	while (ft_strncmp(ptr, word, word_length))
		ptr++;
	if (!(*ptr))
		return ;
	ft_moveptr(&ptr, word_length);
	new_string = ft_strdup(ptr);
	free(*s);
	*s = new_string;
}
