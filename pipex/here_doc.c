/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseptimu <aseptimu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 15:49:14 by aseptimu          #+#    #+#             */
/*   Updated: 2022/03/31 12:14:08 by aseptimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include "builtin.h"

static void	ft_init(t_heredoc *hdoc)
{
	hdoc->buf_msg = NULL;
	hdoc->tmp = NULL;
	hdoc->msg = NULL;
	hdoc->tmp_buf[1] = '\0';
}

static char	*input_reader(char *word, t_heredoc *hdoc)
{
	char	*fre;

	ft_init(hdoc);
	hdoc->word_len = ft_strlen(word);
	while (!hdoc->buf_msg || !((ft_strncmp(hdoc->buf_msg, word, hdoc->word_len) \
	== 0) && (ft_strlen(hdoc->buf_msg) - 1 == (size_t)hdoc->word_len)))
	{
		fre = hdoc->msg;
		hdoc->msg = ft_strjoin(hdoc->msg, hdoc->buf_msg);
		free(fre);
		free(hdoc->buf_msg);
		hdoc->buf_msg = NULL;
		hdoc->buf_msg = readline("> ");
		if (hdoc->buf_msg == NULL)
		{
			free(hdoc->buf_msg);
			return (hdoc->msg);
		}
		fre = hdoc->buf_msg;
		hdoc->buf_msg = ft_strjoin(hdoc->buf_msg, "\n");
		free(fre);
	}
	free(hdoc->buf_msg);
	return (hdoc->msg);
}

static void	child_proc(t_heredoc hdoc, char *word)
{
	set_unset_ctrl_c(0);
	signal(SIGINT, herd_sig);
	hdoc.msg = input_reader(word, &hdoc);
	hdoc.msg_len = ft_strlen(hdoc.msg);
	write(hdoc.fd, hdoc.msg, hdoc.msg_len);
	free(hdoc.msg);
	close(hdoc.fd);
	exit(EXIT_SUCCESS);
}

static int	parent_proc(t_heredoc hdoc)
{
	waitpid(hdoc.pid, &hdoc.status, 0);
	hdoc.fd = open("/tmp/tmpfile_hdoc", O_RDONLY);
	if (hdoc.fd == -1)
		return (err_redir("minishell: ", "tmpfile_hdoc"));
	dup2(hdoc.fd, 0);
	close(hdoc.fd);
	set_unset_ctrl_c(1);
	signal(SIGINT, ft_sigdfl);
	signal(SIGQUIT, ft_sigquit);
	return (WEXITSTATUS(hdoc.status));
}

int	here_doc(char *word, int std_in_out[2])
{
	t_heredoc	hdoc;
	int			ret;

	ret = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	dup2(std_in_out[0], STDIN_FILENO);
	hdoc.fd = open("/tmp/tmpfile_hdoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (hdoc.fd == -1)
		return (err_redir("minishell: ", "tmpfile_hdoc"));
	hdoc.pid = fork();
	if (hdoc.pid == -1)
		return (err_redir("minishell: ", "fork"));
	else if (hdoc.pid == 0)
		child_proc(hdoc, word);
	else
	{
		close(hdoc.fd);
		ret = parent_proc(hdoc);
		if (ret == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (ret);
}
