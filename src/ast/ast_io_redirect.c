/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_io_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyk <seonghyk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:27:43 by seonghyk          #+#    #+#             */
/*   Updated: 2022/12/05 18:27:44 by seonghyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ast.h"
#include "../msh_utils/msh_utils.h"

t_ast_node	*parse_io_here(t_parse_state *state)
{
	t_ast_node	*io_here;
	t_token		*token;
	t_token		*word_token;

	token = get_token(state);
	scan_token(state);
	word_token = get_token(state);
	if (word_token != NULL)
	{
		if (word_token->type == TOKEN_WORD)
		{
			io_here = malloc(sizeof(t_ast_node));
			io_here->type = IO_HERE;
			io_here->data.io_here.token = token;
			io_here->data.io_here.child = NULL;
			scan_token(state);
			return (io_here);
		}
	}
	msh_error(token, MSHERR_SYNTEX);
	return (NULL);
}

t_ast_node	*parse_io_file(t_parse_state *state)
{
	t_ast_node	*io_file;
	t_token		*token;
	t_token		*word_token;

	token = get_token(state);
	scan_token(state);
	word_token = get_token(state);
	if (word_token != NULL)
	{
		if (word_token->type == TOKEN_WORD)
		{
			io_file = malloc(sizeof(t_ast_node));
			io_file->type = IO_FILE;
			io_file->data.io_here.token = token;
			io_file->data.io_here.child = NULL;
			scan_token(state);
			return (io_file);
		}
	}
	msh_error(token, MSHERR_SYNTEX);
	return (NULL);
}

t_ast_node	*parse_io_redirect(t_parse_state *state)
{
	t_token				*token;
	enum e_token_type	t;

	token = get_token(state);
	t = get_token_type(token);
	if (t == TOKEN_LESS || t == TOKEN_GREAT || t == TOKEN_DGREAT)
		return (parse_io_file(state));
	else if (t == TOKEN_DLESS)
		return (parse_io_here(state));
	else
		return (NULL);
}
