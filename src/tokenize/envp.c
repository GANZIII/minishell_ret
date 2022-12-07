/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijoo <jijoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:15:35 by jijoo             #+#    #+#             */
/*   Updated: 2022/12/05 22:36:18 by jijoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "libft.h"

size_t	len_envp(char *env)
{
	size_t	len;

	len = 0;
	while (env[len] != '=')
		len++;
	return (len);
}

int	special(char *line, int idx)
{
	if (line[idx] == ' ' || line[idx] == '\'' || line[idx] == '\"' || \
	line[idx] == '>' || line[idx] == '<' || line[idx] == '$')
		return (1);
	else
		return (0);
}

int	len_var(char *line, int idx)
{
	int	len;

	len = 0;
	while (!(special(line, idx)) && line[idx])
	{
		len++;
		idx++;
	}
	return (len + 5);
}

void	ft_envp(char *line, int *ptr_idx, char *str, char **envp)
{
	char	*var;
	int		edx;

	*ptr_idx += 1;
	var = malloc(len_var(line, *ptr_idx));
	var[0] = '\0';
	while (!special(line, *ptr_idx) && line[*ptr_idx])
	{
		ft_strcat_char(var, line[*ptr_idx]);
		*ptr_idx += 1;
	}
	edx = 0;
	while (envp[edx] && *var)
	{
		if ((len_envp(envp[edx]) == ft_strlen(var)) \
		&& (!ft_strncmp(envp[edx], var, ft_strlen(var))))
			break ;
		edx++;
	}
	if (envp[edx] && *var)
		ft_strcat(str, envp[edx] + len_envp(envp[edx]) + 1);
	free(var);
	*ptr_idx -= 1;
}
