/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijoo <jijoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 21:35:15 by jijoo             #+#    #+#             */
/*   Updated: 2022/12/06 14:46:27 by jijoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]))
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	get_type(char *str)
{
	if (!ft_strcmp(str, "<"))
		return (TOKEN_LESS);
	else if (!ft_strcmp(str, ">"))
		return (TOKEN_GREAT);
	else if (!ft_strcmp(str, "|"))
		return (TOKEN_PIPE);
	else if (!ft_strcmp(str, ">>"))
		return (TOKEN_DGREAT);
	else if (!ft_strcmp(str, "<<"))
		return (TOKEN_DLESS);
	else if (!ft_strcmp(str, "\0"))
		return (TOKEN_NEWLINE);
	else
		return (TOKEN_WORD);
}


void	ji_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
