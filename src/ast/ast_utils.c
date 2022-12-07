/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyk <seonghyk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:24:03 by seonghyk          #+#    #+#             */
/*   Updated: 2022/12/05 18:28:58 by seonghyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "ast.h"

enum e_token_type	get_token_type(t_token *token)
{
	return (token->type);
}

t_token	*get_token(t_parse_state *state)
{
	return (state->current_token);
}

void	scan_token(t_parse_state *state)
{
	if (state->current_token != NULL)
		state->current_token = state->current_token->next;
}

int	is_pair(t_ast_node *node)
{
	if (node->type == PAIR)
		return (1);
	else
		return (0);
}

void	ast_free(t_ast_node *node)
{
	if (node == NULL)
		return ;
	if (is_pair(node))
	{
		ast_free(node->data.pair.left);
		ast_free(node->data.pair.right);
		free(node);
	}
	else
	{
		ast_free(node->data.solo_node.child);
		free(node);
	}
}
