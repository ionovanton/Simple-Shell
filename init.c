/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseptimu <aseptimu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:30:17 by srobt             #+#    #+#             */
/*   Updated: 2022/03/31 15:05:05 by aseptimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_shell(char **envp, t_sh **sh)
{
	(*sh) = malloc(sizeof(t_sh));
	if (!(*sh))
		return (false);
	g_address_sh = *sh;
	if (!dict(0, token_dict, get_value) || !dict(0, string_dict, get_value))
	{
		free(*sh);
		return (false);
	}
	(*sh)->envp = ft_arrdup(envp);
	if (!(*sh)->envp)
	{
		free(*sh);
		dict_destroy(string_dict);
		dict_destroy(token_dict);
		return (false);
	}
	(*sh)->exit_status = 0;
	return (true);
}

int	init_tree(t_sh **sh)
{
	(*sh)->head = malloc(sizeof(t_node));
	if (!(*sh)->head)
	{
		free(*sh);
		return (false);
	}
	(*sh)->head->next = NULL;
	(*sh)->head->args = NULL;
	(*sh)->head->b_prev = NULL;
	(*sh)->head->b_left = NULL;
	(*sh)->head->b_right = NULL;
	(*sh)->head->redir = NULL;
	(*sh)->head->token = TOKEN_ROOT;
	(*sh)->head->pipe = false;
	return (true);
}
