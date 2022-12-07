/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyk <seonghyk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:29:14 by seonghyk          #+#    #+#             */
/*   Updated: 2022/12/05 18:29:15 by seonghyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ast.h"
#include "../msh_utils/msh_utils.h"

t_ast_node	*parse_word(t_parse_state *state)
{
	t_ast_node	*word;
	t_token		*token;

	token = get_token(state);
	scan_token(state);
	if (token->type == TOKEN_WORD)
	{
		word = malloc(sizeof(t_ast_node));
		word->type = WORD_NODE;
		word->data.solo_node.token = token;
		word->data.solo_node.child = NULL;
		return (word);
	}
	else
	{
		msh_error(token, MSHERR_SYNTEX);
		return (NULL);
	}
}

t_ast_node	*create_pipe_sequence(
	t_token *pipe,
	t_ast_node *left,
	t_ast_node *right
)
{
	t_ast_node	*node;
	t_ast_node	*child;

	node = malloc(sizeof(t_ast_node));
	node->type = PIPE_SEQUENCE;
	node->data.simple_command.token = pipe;
	node->data.simple_command.child = malloc(sizeof(t_ast_node));
	child = node->data.simple_command.child;
	child->type = PAIR;
	child->data.pair.left = left;
	child->data.pair.right = right;
	return (node);
}

t_ast_node	*parse_pipe_sequence(t_parse_state *state)
{
	t_ast_node	*lead;
	t_ast_node	*following;
	t_token		*current_token;

	lead = parse_command(state);
	if (lead == NULL)
		return (NULL);
	current_token = get_token(state);
	if (current_token == NULL)
		return (lead);
	if (get_token_type(current_token) == TOKEN_PIPE)
	{
		scan_token(state);
		following = parse_pipe_sequence(state);
		if (following == NULL)
		{
			ast_free(lead);
			return (NULL);
		}
		return (create_pipe_sequence(current_token, lead, following));
	}
	return (lead);
}

t_ast_node	*parse_command(t_parse_state *state)
{
	t_token				*current_token;
	enum e_token_type	t;

	current_token = get_token(state);
	if (current_token == NULL)
		return (NULL);
	t = get_token_type(current_token);
	if (t == TOKEN_NEWLINE)
	{
		scan_token(state);
		msh_error(current_token, MSHERR_SYNTEX);
		return (NULL);
	}
	else if (t == TOKEN_WORD || t == TOKEN_ASSIGNWORD || t == TOKEN_LESS
		|| t == TOKEN_DLESS || t == TOKEN_GREAT || t == TOKEN_DGREAT)
		return (parse_simple_command(state));
	msh_error(current_token, MSHERR_SYNTEX);
	return (NULL);
}

struct s_ast_node	*parse_program(t_token *list)
{
	struct parse_state	parse_state;
	struct s_ast_node	*ret;

	parse_state.token_lst = list;
	parse_state.current_token = list;
	if (get_token_type(get_token(&parse_state)) == TOKEN_NEWLINE)
		scan_token(&parse_state);
	ret = parse_pipe_sequence(&parse_state);
	return (ret);
}
