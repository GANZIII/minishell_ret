/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyk <seonghyk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 00:35:27 by seonghyk          #+#    #+#             */
/*   Updated: 2022/12/05 18:12:33 by seonghyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../minishell.h"
#include "../msh_utils/msh_utils.h"
#include "eval.h"

void	eval_cmd_preffix(t_ast_node *node);
void	eval_cmd_suffix(t_ast_node *node, char ***argv, int idx);

int	msh_builtin_exit(t_ast_node *node, t_context *ctx)
{
	(void)node;
	(void)ctx;
	exit(0);
}

int	msh_builtin_cd(t_ast_node *node, t_context *ctx)
{
	int			result;
	int			number_of_args;
	char		**argv;
	t_ast_node	*pair;

	(void)ctx;
	pair = node->data.simple_command.child;
	get_args_from_cmd_suffix(pair->data.pair.right, &argv, 0);
	number_of_args = -1;
	while (argv[++number_of_args] != NULL)
		;
	if (number_of_args > 0 && number_of_args == 1)
	{
		result = chdir(argv[0]);
		if (result != 0)
			msh_error(node->data.simple_command.token, MSHERR_BUILTIN_CD);
	}
	else
	{
		msh_error(node->data.simple_command.token, MSHERR_BUILTIN_CD);
	}
	free(argv);
	return (0);
}

pid_t	msh_builtin_pwd(t_ast_node *node, t_context *ctx)
{
	char		**argv;
	t_ast_node	*pair;
	pid_t		child_pid;
	char		buf[BUFFER_SIZE];

	pair = node->data.simple_command.child;
	child_pid = fork();
	if (child_pid == 0)
	{
		dup2(ctx->pid[STDIN_FILENO], STDIN_FILENO);
		dup2(ctx->pid[STDOUT_FILENO], STDOUT_FILENO);
		eval_cmd_preffix(pair->data.pair.left);
		eval_cmd_suffix(pair->data.pair.right, &argv, 1);
		argv[0] = node->data.simple_command.token->str;
		getcwd(buf, BUFFER_SIZE);
		printf("%s\n", buf);
		exit(0);
	}
	return (child_pid);
}

pid_t	msh_builtin_echo(t_ast_node *node, t_context *ctx)
{
	char		**argv;
	t_ast_node	*pair;
	pid_t		child_pid;
	int			i;

	pair = node->data.simple_command.child;
	child_pid = fork();
	if (child_pid == 0)
	{
		dup2(ctx->pid[STDIN_FILENO], STDIN_FILENO);
		dup2(ctx->pid[STDOUT_FILENO], STDOUT_FILENO);
		eval_cmd_preffix(pair->data.pair.left);
		eval_cmd_suffix(pair->data.pair.right, &argv, 1);
		argv[0] = node->data.simple_command.token->str;
		i = 1;
		printf("%s", argv[i]);
		while (argv[++i] != NULL)
			printf(" %s", argv[i]);
		printf("\n");
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		exit(0);
	}
	return (child_pid);
}

int	try_eval_simple_command_builtin(t_ast_node *node, t_context *ctx)
{
	if (node->data.simple_command.token == NULL)
		return (-1);
	if (ft_strcmp(node->data.simple_command.token->str, "exit") == 0)
		return (msh_builtin_exit(node, ctx));
	else if (ft_strcmp(node->data.simple_command.token->str, "cd") == 0)
		return (msh_builtin_cd(node, ctx));
	else if (ft_strcmp(node->data.simple_command.token->str, "pwd") == 0)
		return (msh_builtin_pwd(node, ctx));
	else if (ft_strcmp(node->data.simple_command.token->str, "echo") == 0)
		return (msh_builtin_echo(node, ctx));
	else if (ft_strcmp(node->data.simple_command.token->str, "export") == 0)
		return (msh_builtin_export(node, ctx));
	else if (ft_strcmp(node->data.simple_command.token->str, "env") == 0)
		return (msh_builtin_env(node, ctx));
	else if (ft_strcmp(node->data.simple_command.token->str, "unset") == 0)
		return (msh_builtin_unset(node, ctx));
	else
		return (-1);
}
