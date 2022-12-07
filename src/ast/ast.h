/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyk <seonghyk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:27:51 by seonghyk          #+#    #+#             */
/*   Updated: 2022/12/05 18:28:42 by seonghyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H
# include "../minishell.h"

typedef struct s_ast_node	t_ast_node;

typedef struct s_ast_node_solo {
	t_token		*token;
	t_ast_node	*child;
}	t_ast_node_solo;

typedef struct s_ast_node_pair {
	t_ast_node	*left;
	t_ast_node	*right;
}	t_ast_node_pair;

enum e_ast_node_type {
	PIPE_SEQUENCE,
	SIMPLE_COMMAND,
	CMD_PREFFIX,
	CMD_SUFFIX,
	IO_FILE,
	IO_HERE,
	WORD_NODE,
	ASSIGN_WORD_NODE,
	PAIR
};

typedef t_ast_node_solo		t_io_here;
typedef t_ast_node_solo		t_io_file;
typedef t_ast_node_solo		t_ast_simple_command;
typedef t_ast_node_solo		t_ast_pipe_sequence;
typedef t_ast_node_solo		t_ast_cmd_preffix;
typedef t_ast_node_solo		t_ast_cmd_suffix;

union u_ast_node_data {
	t_ast_simple_command	simple_command;
	t_ast_cmd_preffix		cmd_preffix;
	t_ast_cmd_suffix		cmd_suffix;
	t_ast_node_pair			pair;
	t_io_here				io_here;
	t_ast_node_solo			solo_node;
	t_ast_pipe_sequence		pipe_seq;
};

typedef struct s_ast_node {
	enum e_ast_node_type	type;
	union u_ast_node_data	data;
}	t_ast_node;

typedef struct parse_state {
	t_token				*token_lst;
	t_token				*current_token;
}	t_parse_state;

enum e_token_type	get_token_type(t_token *token);
t_token				*get_token(t_parse_state *state);
t_token				*get_next_token(t_parse_state *state);
void				scan_token(t_parse_state *state);
int					token_is_type(t_token *token, enum e_token_type *types);
t_ast_node			*parse_simple_command(t_parse_state *state);
t_ast_node			*parse_command(t_parse_state *state);
t_ast_node			*parse_pipe_sequence(t_parse_state *state);
t_ast_node			*parse_program(t_token *list);
void				ast_free(t_ast_node *node);
t_ast_node			*parse_word(t_parse_state *state);
t_ast_node			*parse_io_redirect(t_parse_state *state);
t_ast_node			*parse_assign_word(t_parse_state *state);
t_ast_node			*parse_cmd_preffix(t_parse_state *state);

#endif
