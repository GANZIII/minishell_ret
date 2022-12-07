/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyk <seonghyk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:13:13 by seonghyk          #+#    #+#             */
/*   Updated: 2022/12/05 18:13:14 by seonghyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVAL_H
# define EVAL_H
# include <errno.h>
# include "../minishell.h"
# include "../ast/ast.h"
# define BUFFER_SIZE 1024
# define PATH_DELIMITER ':'

typedef struct s_context {
	int	pid[2];
	int	close_fd;
}	t_context;

void	eval_io_redirection(t_ast_node *node);
int		eval_nodes(t_ast_node *node, t_context *ctx);
void	eval(t_ast_node *node);
int		is_builtin(t_token *token);
int		msh_builtin_exit(t_ast_node *node, t_context *ctx);
int		msh_builtin_cd(t_ast_node *node, t_context *ctx);
int		msh_builtin_pwd(t_ast_node *node, t_context *ctx);
int		msh_builtin_echo(t_ast_node *node, t_context *ctx);
pid_t	msh_builtin_export(t_ast_node *node, t_context *ctx);
pid_t	msh_builtin_env(t_ast_node *node, t_context *ctx);
pid_t	msh_builtin_unset(t_ast_node *node, t_context *ctx);
void	get_args_from_cmd_suffix(t_ast_node *node, char ***argv, int idx);
int		try_eval_simple_command_builtin(t_ast_node *node, t_context *ctx);
pid_t	eval_simple_command(t_ast_node *node, t_context *ctx);
#endif