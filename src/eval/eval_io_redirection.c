/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_io_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyk <seonghyk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 03:10:06 by seonghyk          #+#    #+#             */
/*   Updated: 2022/12/04 13:58:38 by seonghyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "eval.h"
#include "utils.h"
#include "libft.h"
#include "../msh_utils/msh_utils.h"

#define HEREDOC_TMP "msh_here"

int	eval_here_doc_open_temp_file(char *delimiter)
{
	char	*line;
	char	*expanded_line;
	int		fd;

	fd = open(HEREDOC_TMP, O_CREAT | O_WRONLY, 0664);
	line = readline("heredoc> ");
	while (ft_strcmp(line, delimiter) != 0)
	{
		expanded_line = msh_alloc_expanded_line(line, g_shell_state.envp);
		msh_expand_line(line, expanded_line, g_shell_state.envp);
		ft_putstr_fd(expanded_line, fd);
		ft_putchar_fd('\n', fd);
		free(expanded_line);
		free(line);
		line = readline("heredoc> ");
	}
	close(fd);
	fd = open(HEREDOC_TMP, O_RDONLY);
	unlink(HEREDOC_TMP);
	return (fd);
}

int	eval_here_doc(char *delimiter)
{
	int	fd_temp_in;
	int	temp_file_fd;

	fd_temp_in = dup(STDIN_FILENO);
	dup2(g_shell_state.orig_stdin, STDIN_FILENO);
	dup2(fd_temp_in, STDIN_FILENO);
	temp_file_fd = eval_here_doc_open_temp_file(delimiter);
	close(fd_temp_in);
	if (dup2(temp_file_fd, STDIN_FILENO) == -1)
		return (-1);
	close(temp_file_fd);
	return (STDIN_FILENO);
}

void	eval_io_redirection(t_ast_node *node)
{
	char	*file_path;
	int		fd;

	file_path = node->data.io_here.token->next->str;
	if (get_token_type(node->data.io_here.token) == TOKEN_LESS)
		fd = ppx_redirect2stdin(file_path);
	else if (get_token_type(node->data.io_here.token) == TOKEN_GREAT)
		fd = ppx_redirect2stdout(file_path);
	else if (get_token_type(node->data.io_here.token) == TOKEN_DGREAT)
		fd = ppx_appending_redirect2stdout(file_path);
	else if (get_token_type(node->data.io_here.token) == TOKEN_DLESS)
		fd = eval_here_doc(file_path);
	else
		fd = -1;
	if (fd == -1)
	{
		if (errno == ENOENT)
			msh_error(node->data.io_here.token->next, MSHERR_FILE);
		else if (errno == EACCES)
			msh_error(node->data.io_here.token->next, MSHERR_FILE);
		else if (errno == EISDIR)
			msh_error(node->data.io_here.token->next, MSHERR_FILE);
	}
}
