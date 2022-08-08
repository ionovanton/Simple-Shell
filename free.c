/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:37:07 by srobt             #+#    #+#             */
/*   Updated: 2022/03/29 03:04:57 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tree(t_sh **sh)
{	
	free_node_chain(&(*sh)->head);
}

void	free_redir_chain(t_redir **redir)
{
	t_redir	*tmp;
	t_redir	*cur;

	cur = *redir;
	while (cur)
	{
		tmp = cur->next;
		ft_free_string(&cur->filename);
		free(cur);
		cur = NULL;
		cur = tmp;
	}
	*redir = NULL;
}

void	free_node_chain(t_node **node)
{
	t_node	*tmp;
	t_node	*cur;

	cur = *node;
	while (cur)
	{
		tmp = cur->next;
		ft_free_array(&cur->args);
		free_redir_chain(&cur->redir);
		free(cur);
		cur = NULL;
		cur = tmp;
	}
	*node = NULL;
}

void	free_shell(t_sh **sh)
{
	dict_destroy(token_dict);
	dict_destroy(string_dict);
	free((*sh)->head);
	(*sh)->head = NULL;
	ft_free_array(&(*sh)->envp);
	free(*sh);
	*sh = NULL;
}

void	free_terminate(int code, t_sh **sh)
{
	free_shell(sh);
	exit(code);
}
