/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijoo <jijoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:22:10 by jijoo             #+#    #+#             */
/*   Updated: 2022/12/06 14:23:08 by jijoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipe_redi2(char *line, int *idx_ptr, int *head_ptr, t_token **genesis)
{
	if (line[*idx_ptr] == '<')
	{
		if (line[*idx_ptr + 1] != '<')
		{
			add_token((*head_ptr)--, genesis, ft_strdup("<"));
			*idx_ptr += 1;
		}
		else
		{
			add_token((*head_ptr)--, genesis, ft_strdup("<<"));
			*idx_ptr += 2;
		}
	}
}

void	pipe_redi(char *line, int *idx_ptr, int *head_ptr, t_token **genesis)
{
	if (line[*idx_ptr] == '|')
	{
		add_token((*head_ptr)--, genesis, ft_strdup("|"));
		*idx_ptr += 1;
	}
	else if (line[*idx_ptr] == '>')
	{
		if (line[*idx_ptr + 1] != '>')
		{
			add_token((*head_ptr)--, genesis, ft_strdup(">"));
			*idx_ptr += 1;
		}
		else
		{
			add_token((*head_ptr)--, genesis, ft_strdup(">>"));
			*idx_ptr += 2;
		}
	}
	else
		pipe_redi2(line, idx_ptr, head_ptr, genesis);
}