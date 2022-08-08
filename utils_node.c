/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseptimu <aseptimu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 19:47:18 by srobt             #+#    #+#             */
/*   Updated: 2022/03/31 15:36:16 by aseptimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	node_command(char **data, t_node **new)
{
	(*new)->args = data;
	(*new)->pipe = true;
	return (true);
}

int	node_depressing_emptiness_and_void(t_node **new)
{
	(*new)->args = NULL;
	(*new)->pipe = false;
	return (true);
}

int	node_add(int token, void *data, t_node **new)
{
	(*new) = malloc(sizeof(t_node));
	if (!(*new))
		sh_exit(FAIL);
	(*new)->token = token;
	(*new)->b_left = NULL;
	(*new)->b_prev = NULL;
	(*new)->b_right = NULL;
	(*new)->next = NULL;
	(*new)->redir = NULL;
	if (token == TOKEN_CMD)
		return (node_command((char **)data, new));
	else
		return (node_depressing_emptiness_and_void(new));
	return (true);
}

static int	add(char **data, t_redir **new, t_redir **cur)
{
	char	*token;

	(*new) = malloc(sizeof(t_redir));
	if (!(*new))
		return (false);
	token = par_get_token(*data);
	(*new)->token = (long long)dict(token, token_dict, get_key);
	ft_remove_word(data, token);
	(*new)->filename = *data;
	(*new)->next = NULL;
	ft_free_string(&token);
	if (!cur)
		return (true);
	(*cur)->next = (*new);
	(*cur) = (*cur)->next;
	return (true);
}

int	redir_add(char **args, t_node **node)
{
	const int	length = ft_arrlen(args);
	t_redir		*new;
	t_redir		*cur;
	int			i;

	i = 0;
	if (length > 0)
	{
		if (!add(&args[i++], &(*node)->redir, NULL))
			sh_exit(FAIL);
	}
	else
		return (true);
	cur = (*node)->redir;
	while (i < length)
	{
		if (!add(&args[i++], &new, &cur))
			sh_exit(FAIL);
	}
	return (true);
}
