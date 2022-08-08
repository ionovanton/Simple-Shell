/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 19:01:16 by aseptimu          #+#    #+#             */
/*   Updated: 2022/03/27 19:13:51 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

typedef struct s_env
{
	char			*name;
	char			*arg;
	struct s_env	*next;
}				t_env;

int		isbuiltin(char **args);
int		builtin(char **args, int flag, char ***envp, int ecode);
int		echo(char **argv);
int		pwd(void);
int		cd(char **path, t_env *env);
int		ft_env(char **argc, char **envp);
void	ft_exit(int code, char **args);
int		ft_export(char **args, t_env **env);
int		ft_unset(char **args, t_env **env);

/* utils.c */
char	*take_env_var(t_env *env, char *var);
int		ft_strnotcharlen(char *str, char c);
char	**free_envp(char ***envp);
int		ft_cd_errors(char *putstr, char *perr, int code);
void	ft_malloc_error(void);

/*	env_struct routine */
t_env	*get_env_struct(char **envp);
char	**restore_envp(t_env *env);

/* env_struct_utils */
void	free_env_struct(t_env **env);
t_env	*new_env(char *arg);
t_env	*env_add_node(t_env *env, t_env *new);
int		env_lstsize(t_env *env);
void	env_node_del(t_env **env, char *name);

/* export_utils */
void	sort_envp(char **tmp_envp);
int		check_export_input(char *args);
char	**export_joiner(t_env *tmp_lst, char **tmp_envp, int i);
int		check_plus(char *arg);
int		export_err(char *args);

void	export_add(t_env **env, char *args);

#endif