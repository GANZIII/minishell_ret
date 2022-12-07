/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_simple_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyk <seonghyk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:00:11 by seonghyk          #+#    #+#             */
/*   Updated: 2022/12/05 18:09:52 by seonghyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "eval.h"
#include "libft.h"
#include "../msh_utils/msh_utils.h"

int	ft_execvpe(char *path, char **argv, char **envp)
{
	static char	path_buf[BUFFER_SIZE];
	char		**paths;
	int			i;
	int			result;

	i = -1;
	result = 0;
	if (execve(path, argv, envp) == -1 && errno != ENOENT)
		return (-1);
	while (!result && envp[++i] != NULL)
		result = str_start_with(envp[i], "PATH=");
	if (result == 0)
		return (-1);
	paths = ft_split(&envp[i][ft_strlen("PATH=")], PATH_DELIMITER);
	i = -1;
	while (paths[++i] != NULL)
	{
		ft_strlcpy(path_buf, paths[i], BUFFER_SIZE);
		ft_strlcat(path_buf, "/", BUFFER_SIZE);
		ft_strlcat(path_buf, path, BUFFER_SIZE);
		if (access(path_buf, X_OK) == 0)
			execve(path_buf, argv, envp);
	}
	free(paths);
	return (-1);
}

void	eval_cmd_preffix(t_ast_node *node)
{
	t_token		*token;
	t_ast_node	*next;

	if (node == NULL)
	{
		return ;
	}
	next = node->data.cmd_suffix.child;
	token = node->data.cmd_suffix.token;
	if (token->type == TOKEN_WORD)
	{
		eval_cmd_preffix(next);
	}
	else
	{
		eval_io_redirection(node);
		eval_cmd_preffix(next);
	}
}

void	eval_cmd_suffix(t_ast_node *node, char ***argv, int idx)
{
	t_token		*token;
	t_ast_node	*next;

	if (node == NULL)
	{
		*argv = (char **)malloc(sizeof(char *) * (idx + 2));
		(*argv)[idx] = NULL;
		(*argv)[idx + 1] = NULL;
		return ;
	}
	next = node->data.cmd_suffix.child;
	token = node->data.cmd_suffix.token;
	if (token->type == TOKEN_WORD)
	{
		eval_cmd_suffix(next, argv, idx + 1);
		(*argv)[idx] = token->str;
	}
	else
	{
		eval_io_redirection(node);
		eval_cmd_suffix(next, argv, idx);
	}
}

pid_t	eval_simple_command_utility(t_ast_node *node, t_context *ctx)
{
	char		**argv;
	t_ast_node	*pair;
	pid_t		child_pid;

	pair = node->data.simple_command.child;
	child_pid = fork();
	if (child_pid == 0)
	{
		dup2(ctx->pid[STDIN_FILENO], STDIN_FILENO);
		dup2(ctx->pid[STDOUT_FILENO], STDOUT_FILENO);
		eval_cmd_preffix(pair->data.pair.left);
		eval_cmd_suffix(pair->data.pair.right, &argv, 1);
		argv[0] = node->data.simple_command.token->str;
		if (ctx->close_fd >= 0)
			close(ctx->close_fd);
		ft_execvpe(argv[0], argv, g_shell_state.envp);
		if (errno == EACCES)
			msh_error(node->data.simple_command.token, MSHERR_CMD_PERMMISION);
		msh_error(node->data.simple_command.token, MSHERR_CMD_NOT_FOUND);
	}
	return (child_pid);
}

pid_t	eval_simple_command(t_ast_node *node, t_context *ctx)
{
	pid_t		child_pid;
	int			result;

	result = try_eval_simple_command_builtin(node, ctx);
	if (result >= 0)
	{
		child_pid = result;
	}
	else
	{
		child_pid = eval_simple_command_utility(node, ctx);
	}
	return (child_pid);
}
