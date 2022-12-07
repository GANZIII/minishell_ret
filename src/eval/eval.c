/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyk <seonghyk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 00:34:40 by seonghyk          #+#    #+#             */
/*   Updated: 2022/12/05 18:07:52 by seonghyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "eval.h"
#include "libft.h"
#include "../msh_utils/msh_utils.h"

struct s_shell_state	g_shell_state;

pid_t	eval_pipe_sequence(t_ast_node *node, t_context *ctx)
{
	int				pipe_fd[2];
	t_ast_node_pair	pair;
	t_context		nctx;
	pid_t			child_pid;

	pair = node->data.pipe_seq.child->data.pair;
	pipe(pipe_fd);
	child_pid = fork();
	nctx = *ctx;
	if (child_pid == 0 && pair.left != NULL)
	{
		nctx.pid[STDIN_FILENO] = ctx->pid[STDIN_FILENO];
		nctx.pid[STDOUT_FILENO] = pipe_fd[STDOUT_FILENO];
		nctx.close_fd = pipe_fd[STDIN_FILENO];
		child_pid = eval_simple_command(pair.left, &nctx);
		waitpid(child_pid, NULL, 0);
		exit(0);
	}
	nctx.pid[STDOUT_FILENO] = ctx->pid[STDOUT_FILENO];
	nctx.pid[STDIN_FILENO] = pipe_fd[STDIN_FILENO];
	nctx.close_fd = pipe_fd[STDOUT_FILENO];
	close(pipe_fd[1]);
	if (pair.right->type == SIMPLE_COMMAND)
		return (eval_simple_command(pair.right, &nctx));
	return (eval_pipe_sequence(pair.right, &nctx));
}

pid_t	eval_nodes(t_ast_node *node, t_context *ctx)
{
	if (node->type == PIPE_SEQUENCE)
		return (eval_pipe_sequence(node, ctx));
	else if (node->type == SIMPLE_COMMAND)
		return (eval_simple_command(node, ctx));
	else
		return (0);
}

void	eval(t_ast_node *node)
{
	t_context	ctx;
	pid_t		last_cmd;
	int			wstatus;

	wstatus = 0;
	ctx.pid[STDIN_FILENO] = STDIN_FILENO;
	ctx.pid[STDOUT_FILENO] = STDOUT_FILENO;
	ctx.close_fd = -1;
	last_cmd = eval_nodes(node, &ctx);
	waitpid(last_cmd, &wstatus, 0);
	while (wait(NULL) != -1)
		;
	if (last_cmd > 0)
		g_shell_state.exit_status = WEXITSTATUS(wstatus);
}
