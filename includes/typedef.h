/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 15:49:35 by srobt             #+#    #+#             */
/*   Updated: 2022/03/28 20:53:20 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

# include "minishell.h"

typedef struct s_redir
{
	int				token;
	char			*filename;
	struct s_redir	*next;
}	t_redir;

typedef struct s_node
{
	int				token;
	bool			pipe;
	char			**args;
	struct s_redir	*redir;
	struct s_node	*next;
	struct s_node	*b_left;
	struct s_node	*b_right;
	struct s_node	*b_prev;
}	t_node;

typedef struct s_sh
{
	int				exit_status;
	struct s_node	*head;
	char			**envp;
}	t_sh;

typedef struct s_lexer
{
	char	*nptr;
	char	*optr;
	char	**envp;
	int		ecode;
	int		sep;
}	t_lexer;

typedef struct s_matrix
{
	int	**mat;
	int	w;
	int	h;
}	t_matrix;

typedef struct s_enve
{
	char	*new_str;
	char	*optr;
	char	*nptr;
	char	*value;
	char	*key;
	int		n;
}	t_enve;

#endif
