/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijoo <jijoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 21:22:33 by jijoo             #+#    #+#             */
/*   Updated: 2022/12/04 17:06:34 by jijoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	single_quote(char *line, int *ptr_idx, char *str)
{
	while (line[++(*ptr_idx)] != '\'')
		ft_strcat_char(str, line[*ptr_idx]);
}

void	double_quote(char *line, int *ptr_idx, char *str, char **envp)
{
	while (line[++(*ptr_idx)] != '\"')
	{
		if (line[*ptr_idx] == '$')
			ft_envp(line, ptr_idx, str, envp);
		else
			ft_strcat_char(str, line[*ptr_idx]);
	}
}

void	no_quote(char *line, int *ptr_idx, char *str, char **envp)
{
	char	*str_status;

	if (line[*ptr_idx] == '$')
	{
		if (line[*ptr_idx + 1] == '?')
		{
			str_status = ft_itoa2(g_shell_state.exit_status);
			ft_strcat(str, str_status);
			free(str_status);
			*ptr_idx += 1;
		}
		else
			ft_envp(line, ptr_idx, str, envp);
	}
	else
		ft_strcat_char(str, line[*ptr_idx]);
}

void	quote_err(char *line)
{
	printf("quote error\n");
	free(line);
}
