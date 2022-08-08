/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 23:52:34 by srobt             #+#    #+#             */
/*   Updated: 2022/03/29 00:50:06 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# define SHELL_NAME			"minishell>: "

// Lexer
# define ANY				"ANY"
# define NONE				"NONE"
# define T_AND				"<T_AND>"
# define T_OR				"<T_OR>"
# define T_SEP				"<T_SEP>"
# define T_PIPE				"<T_PIPE>"
# define T_LESS				"<T_LESS>"
# define T_GREAT			"<T_GREAT>"
# define T_LESSLESS			"<T_LESSLESS>"
# define T_GREATGREAT		"<T_GREATGREAT>"
# define T_SPACE			"<T_SPACE>"
# define T_AQ				"<T_AQ>"
# define T_BQ				"<T_BQ>"

// Tokens
# define TOKEN_NONE			0		// NONE
# define TOKEN_OR			1		// ||
# define TOKEN_PIPE			2		// |
# define TOKEN_GREATGREAT	3		// >>
# define TOKEN_GREAT		4		// >
# define TOKEN_LESSLESS		5		// <<
# define TOKEN_LESS			6		// <
# define TOKEN_AND			7		// &&
# define TOKEN_BEFORE		8		// &
# define TOKEN_SEP			9		// <T_SEP>
# define TOKEN_SPACE		10		// <T_SPACE>
# define TOKEN_AQ			11		// <T_AQ>
# define TOKEN_BQ			12		// <T_BQ>
# define TOKEN_LIST_LENGTH	13
# define TOKEN_CMD			12		// command
# define TOKEN_FILE			13		// file
# define TOKEN_ROOT			14		// root node
# define SUCCESS			0
# define FAIL				1

// Characters
# define C_PIPE				'|'
# define C_ENV				'$'
# define C_LESS				'<'
# define C_GREAT			'>'
# define C_SPACE			' '
# define C_AMP				'&'
# define C_ECODE			'?'
# define C_DQ				34
# define C_SQ				39

// Strings
# define S_DQ				"\""
# define S_SQ				"\'"
# define S_AND				"&&"
# define S_BEFORE			"&"
# define S_OR				"||"
# define S_PIPE				"|"
# define S_ENV				"$"
# define S_ECODE			"?"
# define S_LESSLESS			"<<"
# define S_LESS				"<"
# define S_GREATGREAT		">>"
# define S_GREAT			">"

// Pattern matching
# define E					'$'
# define T					1
# define F					0
# define N					-1
# define ASTERISK			'*'

#endif
