/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_simple_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyk <seonghyk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:19:49 by seonghyk          #+#    #+#             */
/*   Updated: 2022/12/05 18:44:20 by seonghyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ast.h"
#include "../msh_utils/msh_utils.h"

t_ast_node	*create_cmd_preffix(t_token *lead, t_ast_node *following)
{
	t_ast_node	*ret;

	ret = malloc(sizeof(t_ast_node));
	ret->type = CMD_PREFFIX;
	ret->data.cmd_preffix.token = lead;
	ret->data.cmd_preffix.child = following;
	return (ret);
}

t_ast_node	*create_cmd_suffix(t_token *following, t_ast_node *lead)
{
	t_ast_node	*ret;

	ret = malloc(sizeof(t_ast_node));
	ret->type = CMD_SUFFIX;
	ret->data.cmd_suffix.token = following;
	ret->data.cmd_suffix.child = lead;
	return (ret);
}

t_ast_node	*parse_cmd_suffix(t_parse_state *state)
{
	struct s_ast_node	*following;
	struct s_ast_node	*lead;
	struct s_token		*current_token;

	current_token = get_token(state);
	if (current_token == NULL)
		return (NULL);
	if (get_token_type(current_token) == TOKEN_WORD)
		lead = parse_word(state);
	else if (get_token_type(current_token) == TOKEN_DGREAT
		|| get_token_type(current_token) == TOKEN_LESS
		|| get_token_type(current_token) == TOKEN_DLESS
		|| get_token_type(current_token) == TOKEN_GREAT)
		lead = parse_io_redirect(state);
	else
		return (NULL);
	following = parse_cmd_suffix(state);
	if (lead != NULL)
		lead->data.cmd_suffix.child = following;
	return (lead);
}

t_ast_node	*create_simple_command(
	t_token *word,
	t_ast_node *preffix,
	t_ast_node *suffix
)
{
	t_ast_node	*node;
	t_ast_node	*child;

	node = malloc(sizeof(t_ast_node));
	node->type = SIMPLE_COMMAND;
	node->data.simple_command.token = word;
	node->data.simple_command.child = malloc(sizeof(t_ast_node));
	child = node->data.simple_command.child;
	child->type = PAIR;
	child->data.pair.left = preffix;
	child->data.pair.right = suffix;
	return (node);
}

t_ast_node	*parse_simple_command(t_parse_state *state)
{
	t_ast_node	*preffix;
	t_ast_node	*suffix;
	t_token		*word;

	preffix = parse_cmd_preffix(state);
	word = get_token(state);
	suffix = NULL;
	if (word != NULL)
	{
		if (word->type == TOKEN_WORD)
			scan_token(state);
		else
		{
			ast_free(preffix);
			return (NULL);
		}
		suffix = parse_cmd_suffix(state);
	}
	return (create_simple_command(word, preffix, suffix));
}
