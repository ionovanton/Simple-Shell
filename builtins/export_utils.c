/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseptimu <aseptimu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 16:47:09 by aseptimu          #+#    #+#             */
/*   Updated: 2022/03/27 12:14:42 by aseptimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin.h"

int	export_err(char *args)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(args, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}

void	sort_envp(char **tmp_envp)
{
	int		i;
	char	*tmp;

	i = 0;
	while (tmp_envp[i + 1])
	{
		if (ft_strncmp(tmp_envp[i], tmp_envp[i + 1], \
		ft_strlen(tmp_envp[i] + 1)) > 0)
		{
			tmp = tmp_envp[i];
			tmp_envp[i] = tmp_envp[i + 1];
			tmp_envp[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
}

int	check_export_input(char *args)
{
	int	i;

	if (!(ft_isalpha(args[0]) || args[0] == '_'))
		return (-1);
	i = 0;
	while (args[i] && args[i] != '=')
	{
		if (!((args[i] == '+' && args[i + 1] == '=') || ft_isalnum(args[i]) \
			|| args[i] == '_'))
			return (-1);
		i++;
	}
	return (0);
}

char	**export_joiner(t_env *tmp_lst, char **tmp_envp, int i)
{
	char	*tmp;

	tmp_envp[i] = ft_strjoin(tmp_lst->name, "=\"");
	if (!tmp_envp[i])
		return (free_envp(&tmp_envp));
	tmp = tmp_envp[i];
	tmp_envp[i] = ft_strjoin(tmp_envp[i], tmp_lst->arg);
	free(tmp);
	if (!tmp_envp[i])
		return (free_envp(&tmp_envp));
	tmp = tmp_envp[i];
	tmp_envp[i] = ft_strjoin(tmp_envp[i], "\"\n");
	free(tmp);
	if (!tmp_envp[i])
		return (free_envp(&tmp_envp));
	return (tmp_envp);
}

int	check_plus(char *arg)
{
	while (*arg && *arg != '=')
	{
		if (ft_strncmp(arg, "+=", 2) == 0)
			return (1);
		arg++;
	}
	return (0);
}
