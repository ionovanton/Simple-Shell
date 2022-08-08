/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseptimu <aseptimu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:20:06 by srobt             #+#    #+#             */
/*   Updated: 2022/03/31 16:37:11 by aseptimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sh	*g_address_sh;

static void	control(char *str, t_sh *sh)
{
	if (!str)
	{
		ft_putstr_fd("\x1b[1A", STDERR_FILENO);
		ft_putstr_fd("\033[12C", STDERR_FILENO);
		ft_putstr_fd("exit\n", STDERR_FILENO);
		free_shell(&sh);
		exit(1);
	}
	add_history(str);
	lexer(&str, sh);
	parser(&str, sh);
	set_unset_ctrl_c(1);
	signal(SIGINT, ft_sigdfl);
	signal(SIGQUIT, ft_sigquit);
	if (sh->head)
		sh->exit_status = pipex(sh->head->next, &sh->envp, sh->exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_sh	*sh;

	(void)argc;
	rl_outstream = stderr;
	argv++;
	if (!init_shell(envp, &sh) || !check_env(&sh->envp))
		exit (FAIL);
	while (1)
	{
		set_unset_ctrl_c(0);
		signal(SIGINT, ft_slashnsig);
		signal(SIGQUIT, SIG_IGN);
		str = readline(SHELL_NAME);
		if (!init_tree(&sh))
			sh_exit(FAIL);
		if (!str || str[0] != '\0')
			control(str, sh);
		free_tree(&sh);
	}
	return (sh->exit_status);
}
