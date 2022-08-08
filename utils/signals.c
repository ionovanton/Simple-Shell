/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:21:08 by aseptimu          #+#    #+#             */
/*   Updated: 2022/03/27 14:00:17 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

void	set_unset_ctrl_c(int flag)
{
	struct termios	p_term;

	tcgetattr(STDIN_FILENO, &p_term);
	if (flag == 0)
		p_term.c_lflag &= ~ECHOCTL;
	else
		p_term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, 0, &p_term);
}

void	ft_slashnsig(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_sigdfl(int signum)
{
	(void)signum;
	write(1, "\n", 1);
}

void	ft_sigquit(int signum)
{
	(void)signum;
	write(1, "Quit: 3\n", 8);
}

void	herd_sig(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	exit(1);
}
