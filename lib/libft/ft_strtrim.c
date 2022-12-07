/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyk <seonghyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 17:18:06 by seonghyk          #+#    #+#             */
/*   Updated: 2022/03/29 20:05:09 by seonghyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	g_trim_set[256];

static int	_ft_is_in_set(char c)
{
	return (g_trim_set[(unsigned char)c] == 1);
}

static char const	*_ft_init_trim(char const *s1, char const *set)
{
	size_t	len;

	if (set == NULL || s1 == NULL)
		return (NULL);
	len = 0;
	while (set[len] != 0)
		g_trim_set[(unsigned char)set[len++]] = 1;
	return (s1);
}

static void	_ft_free_trim_set(char const *set)
{
	size_t	len;

	len = 0;
	while (set[len] != 0)
		g_trim_set[(unsigned char)set[len++]] = 0;
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	idx_s;
	size_t	idx_d;
	size_t	start;
	char	*dst;

	if (_ft_init_trim(s1, set) == NULL)
		return (NULL);
	start = 0;
	while (_ft_is_in_set(s1[start]))
		start++;
	idx_s = ft_strlen(s1);
	if (idx_s != 0)
		while (_ft_is_in_set(s1[idx_s - 1]) && idx_s - 1 > 0)
			idx_s--;
	if (start >= idx_s)
		idx_s = start;
	dst = (char *)malloc(sizeof(char) * (idx_s - start) + 1);
	if (dst == NULL)
		return (NULL);
	idx_d = idx_s - start;
	dst[idx_d] = '\0';
	while (idx_d > 0 && idx_s > start)
		dst[--idx_d] = s1[--idx_s];
	_ft_free_trim_set(set);
	return (dst);
}
