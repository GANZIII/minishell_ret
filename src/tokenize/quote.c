/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijoo <jijoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 19:37:33 by jijoo             #+#    #+#             */
/*   Updated: 2022/12/04 15:55:14 by jijoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_single_quote(char *str, int *idx_ptr)
{
	while (str[++(*idx_ptr)] != '\'')
	{
		if (str[*idx_ptr] == '\0')
			return (1);
	}
	return (0);
}

int	open_double_quote(char *str, int *idx_ptr)
{
	while (str[++(*idx_ptr)] != '\"')
	{
		if (str[*idx_ptr] == '\0')
			return (1);
	}
	return (0);
}

int	quote_open(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx])
	{
		if (str[idx] == '\'')
		{
			if (open_single_quote(str, &idx))
				return (1);
			idx++;
			continue ;
		}
		else if (str[idx] == '\"')
		{
			if (open_double_quote(str, &idx))
				return (1);
			idx++;
			continue ;
		}
		else
			idx++;
	}
	return (0);
}
