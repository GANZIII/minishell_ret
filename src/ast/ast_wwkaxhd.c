/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_wwkaxod.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyk <seonghyk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:29:28 by seonghyk          #+#    #+#             */
/*   Updated: 2022/12/05 18:29:30 by seonghyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ast.h"
#include "../msh_utils/msh_utils.h"

t_ast_node	*parse_assign_word(t_parse_state *state)
{
	t_ast_node	*word;
	t_token		*token;

	token = get_token(state);
	scan_token(state);
	if (token->type == TOKEN_ASSIGNWORD)
	{
		word = malloc(sizeof(t_ast_node));
		word->type = ASSIGN_WORD_NODE;
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

t_ast_node	*parse_cmd_preffix(t_parse_state *state)
{
	struct s_ast_node	*following;
	struct s_ast_node	*lead;
	struct s_token		*current_token;

	current_token = get_token(state);
	if (current_token == NULL)
		return (NULL);
	if (get_token_type(current_token) == TOKEN_ASSIGNWORD)
		lead = parse_assign_word(state);
	else if (get_token_type(current_token) == TOKEN_DGREAT
		|| get_token_type(current_token) == TOKEN_LESS
		|| get_token_type(current_token) == TOKEN_DLESS
		|| get_token_type(current_token) == TOKEN_GREAT)
		lead = parse_io_redirect(state);
	else
		return (NULL);
	following = parse_cmd_preffix(state);
	if (lead != NULL)
		lead->data.cmd_suffix.child = following;
	return (lead);
}
