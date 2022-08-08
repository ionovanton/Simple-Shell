/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:25:10 by srobt             #+#    #+#             */
/*   Updated: 2022/03/29 01:00:20 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || (c == 32));
}

int	ft_isredir(char c)
{
	return (c == '<' || c == '>');
}

int	ft_issysname(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	ft_isnotsysname(char c)
{
	return (!ft_issysname(c));
}

int	ft_isquote(char c)
{
	return (c == 34 || c == 39);
}
