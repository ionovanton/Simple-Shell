/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseptimu <aseptimu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:57:29 by aseptimu          #+#    #+#             */
/*   Updated: 2022/03/23 14:42:20 by aseptimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"

static char	**join_envp(t_env *env, char **tmp_envp)
{
	int		i;
	t_env	*tmp_lst;

	tmp_lst = env;
	i = 0;
	while (tmp_lst != NULL)
	{
		if (tmp_lst->arg != NULL)
		{
			tmp_envp = export_joiner(tmp_lst, tmp_envp, i);
			if (!tmp_envp[i])
				return (NULL);
		}
		else
		{
			tmp_envp[i] = ft_strjoin(tmp_lst->name, "\n");
			if (!tmp_envp[i])
				return (free_envp(&tmp_envp));
		}
		tmp_lst = tmp_lst->next;
		i++;
	}
	tmp_envp[i] = NULL;
	return (tmp_envp);
}

static char	**create_envp(t_env *env)
{
	char	**ret;

	ret = (char **)malloc((env_lstsize(env) + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	ret = join_envp(env, ret);
	if (!ret)
		return (NULL);
	return (ret);
}

static int	get_output_export(t_env *env)
{
	char	**tmp_envp;
	int		i;

	tmp_envp = create_envp(env);
	if (!tmp_envp)
		exit (EXIT_FAILURE);
	sort_envp(tmp_envp);
	i = 0;
	while (tmp_envp[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(tmp_envp[i], STDOUT_FILENO);
		i++;
	}
	free_envp(&tmp_envp);
	return (EXIT_SUCCESS);
}

static int	set_env(t_env **env, char **args)
{
	int		i;
	int		code;

	i = 1;
	code = EXIT_SUCCESS;
	while (args[i])
	{
		if (check_export_input(args[i]) == 0)
		{
			if (check_plus(args[i]) == 0)
			{
				env_node_del(env, args[i]);
				*env = env_add_node(*env, new_env(args[i]));
			}
			else
				export_add(env, args[i]);
		}
		else
			code = export_err(args[i]);
		i++;
	}
	return (code);
}

int	ft_export(char **args, t_env **env)
{
	int	code;

	if (args[1] == NULL)
		code = get_output_export(*env);
	else
		code = set_env(env, args);
	return (code);
}
