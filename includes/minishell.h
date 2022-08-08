/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 00:39:04 by srobt             #+#    #+#             */
/*   Updated: 2022/03/29 05:06:23 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>				// malloc free exit
# include <stdio.h>					// required by readline
# include <signal.h>
# include <stdbool.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "typedef.h"
# include "libft.h"
# include "pipex.h"
# include "dirent.h"
# include "define.h"

extern t_sh	*g_address_sh;

// Parser
void	parser(char **s, t_sh *sh);
void	par_insert_new_token(char **new_str, char **ptr, int *isstart);
void	par_copy_word(char **new_str, char **s, int *isstart);
void	par_compress_tokens(char ***args);
void	par_strjoin(char **str, char *word);
char	**par_split(char *s, char *sep);
char	*par_get_token(char *s);
char	*par_get_compressed_token(\
long long status, char **token_word, int *isstart);
int		par_get_status(char **ptr, char **token_word);
int		par_skip_token(char **ptr, char *token, int token_length);
int		par_skip_token_once(char **ptr);
int		par_check_token_presence(char *s, char *token, int token_length);
int		par_is_token(char *ptr);

// Lexer
void	lexer(char **s, t_sh *sh);
void	lex_add_quote(t_lexer *l);
void	lex_add_token(t_lexer *l);
void	lex_add_word(t_lexer *l);
void	lex_pattern_matching(char **s);
int		lex_init(int exit_status, char **s, char ***envp, t_lexer **l);
int		lex_check_environ(char *s);
char	*lex_env_getkey(char *s);
void	lex_paste_word(char **s, char *word);
int		lex_env_get_newlength(char *s, char **envp, int ecode);
void	lex_destroy(t_lexer **l);
int		lex_env_get_length(char *key);
void	lex_copyenv(char **key, char **value, char **envp, int ecode);
void	lex_strjoin(char **str, char *word);
int		lex_env_expand(char **s, char **envp, int ecode);
char	*lex_getenv(char *key, char **envp);
void	lex_extended_quotes(t_lexer *l);
int		lex_error_check(t_lexer *l);

// Pattern
int		pattern(char *s, char *p);
int		pat_init_matrix(int w, int h, t_matrix **m);
int		pat_destroy_matrix(t_matrix **m);
char	*pat_convert_string(char *s);
char	**pat_get_filenames(void);

// Dict
void	*dict(void *data, char **(*g)(int), void *(*f)(void *, char **));
void	dict_destroy(char **(*f)(int));
void	*get_key(void *data, char **dict);
void	*get_value(void *data, char **dict);
char	**string_dict(int n);
char	**token_dict(int n);
int		free_dict(char **dict, int n);
int		dict_check_integrity(char **dict, int n);

// Utils node
int		node_add(int token, void *data, t_node **cur);
int		redir_add(char **args, t_node **node);

// Init, Free, Exit
int		init_shell(char **envp, t_sh **sh);
int		init_tree(t_sh **sh);
void	free_shell(t_sh **sh);
void	free_tree(t_sh **sh);
void	free_terminate(int code, t_sh **sh);
void	free_node_chain(t_node **node);
void	free_redir_chain(t_redir **redir);
void	sh_exit(int code);

// Sig & Termcaps
void	ft_slashnsig(int signum);
void	ft_sigdfl(int signum);
void	ft_sigquit(int signum);
void	set_unset_ctrl_c(int flag);
void	herd_sig(int signum);

int		check_env(char ***envp);
int		get_lvl(char *str);

#endif // MINISHELL_H