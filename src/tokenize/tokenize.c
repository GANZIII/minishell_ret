/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijoo <jijoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 19:22:15 by jijoo             #+#    #+#             */
/*   Updated: 2022/12/07 21:30:17 by jijoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_space(char *line, int idx)
{
	while (line[idx] == ' ' || line[idx] == 9)
		idx++;
	return (idx);
}

char	*ft_str(char *line, int idx, char **envp)
{
	char	*tmp;
	int		len;

	len = 0;
	while (line[idx] != ' ' && line[idx])
	{
		if (line[idx] == '\'')
			len += len_str_sq(line, &idx);
		else if (line[idx] == '\"')
			len += len_str_dq(line, &idx, envp);
		else
		{
			if (line[idx] == '$')
				len += search_envp(line, &idx, envp);
			else
				len++;
		}
		if (line[idx])
			idx++;
	}
	tmp = malloc(len + 10);
	tmp[0] = '\0';
	return (tmp);
}

void	add_token(int head, t_token **genesis, char *str)
{
	t_token	*new;

	if (str[0])
	{
		new = ft_lstnew(str);
		if (head > 0)
			(*genesis) = new;
		else
			ft_lstadd_back(genesis, new);
	}
	else
	{
		if (head > 0)
			(*genesis) = ft_lstnew(str);
		else
			ft_lstadd_back(genesis, ft_lstnew(str));
	}
}

void	quote_check(char *line, int *idx_ptr, char *str, char **envp)
{
	if (line[*idx_ptr] == '\'')
		single_quote(line, idx_ptr, str);
	else if (line[*idx_ptr] == '\"')
		double_quote(line, idx_ptr, str, envp);
}

void	make_str(char *line, int *idx_ptr, char *str, char **envp)
{
	if (line[*idx_ptr] == '\'' || line[*idx_ptr] == '\"')
		quote_check(line, idx_ptr, str, envp);
	else
		no_quote(line, idx_ptr, str, envp);
}

void	tokenize(char *line, t_token **genesis, char **envp)
{
	int		idx;
	char	*str;
	int		head;

	head = 1;
	idx = 0;
	while (line[idx] != '\0')
	{
		idx = skip_space(line, idx);
		if (!line[idx])
			break ;
		str = ft_str(line, idx, envp);
		while (line[idx] != ' ' && line[idx] && line[idx] != '|' && line[idx] != '>' && line[idx] != '<')
		{
			make_str(line, &idx, str, envp);
			if (line[idx])
				idx++;
		}
		if (str[0])
			add_token(head--, genesis, str);
		pipe_redi(line, &idx, &head, genesis);
	}
	add_token(head--, genesis, ft_strdup(""));
}
