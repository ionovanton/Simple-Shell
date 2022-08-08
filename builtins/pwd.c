/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseptimu <aseptimu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:46:43 by aseptimu          #+#    #+#             */
/*   Updated: 2022/03/20 13:09:17 by aseptimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"
#include <stdio.h>

int	pwd(void)
{
	char	*dir;

	dir = getcwd((char *) NULL, 0);
	if (dir == NULL)
	{
		perror("minishell: getcwd");
		return (1);
	}
	ft_putstr_fd(dir, 1);
	ft_putchar_fd('\n', 1);
	free(dir);
	return (0);
}
