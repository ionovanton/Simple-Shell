/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:51:22 by aseptimu          #+#    #+#             */
/*   Updated: 2022/03/27 19:34:07 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

static int	result(const char *str, unsigned long long res, int negative)
{
	int					i;
	unsigned long long	kostyl;

	kostyl = 9223372036854775807;
	kostyl++;
	i = 0;
	while (!(*str >= '0' && *str <= '9'))
		str++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if ((res > 9223372036854775807 && negative == 1) \
		|| (res > kostyl && negative == -1) || i > 19)
	{
		if (negative == 1)
			return (255);
		else if (negative == -1)
			return (255);
	}
	return (res * negative);
}

static int	get_lvl_2(char *str, int negative)
{
	unsigned long long	ret;
	char				*tmp;

	ret = 0;
	tmp = str;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-')
	{
		negative = -negative;
		str++;
	}
	else if (*str == '+')
		str++;
	if (*str < '0' || *str > '9')
		return (255);
	while (*str >= '0' && *str <= '9')
	{
		ret = ret * 10 + *str - '0';
		str++;
	}
	if (*str == '\0')
		return (result(tmp, ret, negative));
	else
		return (255);
}

void	ft_exit(int code, char **args)
{
	int	ecode;
	int	negative;

	ecode = 0;
	ft_putstr_fd("exit\n", STDERR_FILENO);
	free_shell(&g_address_sh);
	if (args[1] == NULL)
		exit(code);
	else if (args[2] != NULL)
		exit(1);
	else
	{
		negative = 1;
		ecode = get_lvl_2(args[1], negative);
		exit(ecode);
	}
}
