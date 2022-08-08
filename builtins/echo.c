/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 16:16:30 by aseptimu          #+#    #+#             */
/*   Updated: 2022/03/17 19:45:07 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	echo(char **argv)
{
	int	nflag;

	argv++;
	nflag = 0;
	while (*argv && !ft_strncmp(*argv, "-n", 2))
	{
		++argv;
		nflag = 1;
	}
	while (*argv)
	{
		ft_putstr_fd(*argv, 1);
		if (*++argv)
			ft_putchar_fd(' ', 1);
	}
	if (!nflag)
		ft_putchar_fd('\n', 1);
	return (0);
}
