/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijoo <jijoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 21:19:12 by jijoo             #+#    #+#             */
/*   Updated: 2022/12/04 16:30:58 by jijoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_showlst(t_token **genesis)
{
	t_token	*current;

	current = *genesis;
	while (1)
	{
		printf("str: %s\n", current->str);
		printf("type: %d\n", current->type);
		printf("len: %d\n", current->strlen);
		current = current->next;
		if (current == NULL)
			break ;
	}
}

t_token	*ft_lstnew(char *str)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->str = str;
	new->strlen = ft_strlen(str);
	new->type = get_type(str);
	new->next = NULL;
	return (new);
}

t_token	*ft_lstlast(t_token *token)
{
	if (token == NULL)
		return (NULL);
	while (token->next != NULL)
		token = token->next;
	return (token);
}

void	ft_lstadd_back(t_token **token, t_token *new)
{
	t_token	*last;

	if (token == NULL || new == NULL)
		return ;
	if (*token == NULL)
	{
		*token = new;
		return ;
	}
	last = ft_lstlast(*token);
	new->next = last->next;
	last->next = new;
}

void	ft_lstfree(t_token **lst)
{
	t_token	*tmp;
	t_token	*next;

	if (lst == NULL)
		return ;
	tmp = *lst;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->str);
		free(tmp);
		tmp = next;
	}
}
