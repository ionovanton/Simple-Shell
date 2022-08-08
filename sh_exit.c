/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 23:14:55 by srobt             #+#    #+#             */
/*   Updated: 2022/03/29 18:05:55 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sh	*g_address_sh;

void	sh_exit(int code)
{
	free_tree(&g_address_sh);
	dict_destroy(token_dict);
	dict_destroy(string_dict);
	exit(code);
}
