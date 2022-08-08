/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseptimu <aseptimu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 19:42:53 by srobt             #+#    #+#             */
/*   Updated: 2022/03/31 15:35:22 by aseptimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	loop(char ***args, char ***redir, char ***a)
{
	int	i;

	i = 0;
	while ((*a)[i])
	{
		if (par_check_token_presence((*a)[i], ANY, 3))
			*redir = ft_arradd(redir, (*a)[i]);
		else
			*args = ft_arradd(args, (*a)[i]);
		i++;
	}
}

// We assume that no syntax occured this far.
static int	par_process_command(char *command, t_node **cur)
{
	char	**a;
	char	**args;
	char	**redir;
	int		token;

	args = NULL;
	redir = NULL;
	a = par_split(command, T_SEP);
	if (!a)
		return (false);
	loop(&args, &redir, &a);
	if (args == NULL)
		token = TOKEN_NONE;
	else
		token = TOKEN_CMD;
	if (!node_add(token, args, cur) || !redir_add(redir, cur))
		return (false);
	ft_free_array(&a);
	free(redir);
	return (true);
}

void	parser(char **s, t_sh *sh)
{
	t_node	*cur;
	t_node	*new;
	char	**args;
	int		i;

	if (!sh->head)
		return ;
	cur = sh->head;
	if (ft_strlen(*s) == 0)
		node_add(TOKEN_NONE, NULL, &cur->next);
	args = par_split(*s, T_PIPE);
	par_compress_tokens(&args);
	i = 0;
	while (args[i])
	{
		if (!par_process_command(args[i], &new))
			free_terminate(FAIL, &sh);
		cur->next = new;
		cur = cur->next;
		i++;
	}
	cur->pipe = false;
	ft_free_array(&args);
	ft_free_string(s);
}
