/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijoo <jijoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 18:10:32 by jijoo             #+#    #+#             */
/*   Updated: 2022/12/04 15:56:06 by jijoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_ret_envplen(int exist, int *ptr_idx, char *var, char *env)
{
	if (exist)
	{
		free(var);
		*ptr_idx -= 1;
		return (len_envp(env));
	}
	free(var);
	*ptr_idx -= 1;
	return (0);
}

int	search_envp(char *line, int *ptr_idx, char **envp)
{
	int		edx;
	char	*var;

	var = malloc(100);
	var[0] = '\0';
	*ptr_idx += 1;
	while ((line[*ptr_idx] != ' ') && (line[*ptr_idx] != '\'') \
	&& (line[*ptr_idx] != '\"' && line[*ptr_idx]))
	{
		ft_strcat_char(var, line[*ptr_idx]);
		*ptr_idx += 1;
	}
	edx = 0;
	while (envp[edx] && *var)
	{
		if ((len_envp(envp[edx]) == ft_strlen(var)) \
		&& !ft_strncmp(envp[edx], var, ft_strlen(var)))
			break ;
		edx++;
	}
	if (envp[edx] && *var)
		return (ft_ret_envplen(1, ptr_idx, var, envp[edx]));
	return (ft_ret_envplen(0, ptr_idx, var, envp[edx]));
}

int	len_str_sq(char *line, int *idx_ptr)
{
	int	plus;

	plus = 0;
	while (line[++(*idx_ptr)] != '\'')
		plus++;
	return (plus);
}

int	len_str_dq(char *line, int *idx_ptr, char **envp)
{
	int	plus;

	plus = 0;
	while (line[++(*idx_ptr)] != '\"')
	{
		if (line[*idx_ptr] == '$')
			plus += search_envp(line, idx_ptr, envp);
		else
			plus++;
	}
	return (0);
}
