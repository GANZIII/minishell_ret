/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyk <seonghyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:40:53 by seonghyk          #+#    #+#             */
/*   Updated: 2022/03/29 20:06:55 by seonghyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**_ft_free_ret(char **ret, int count_c)
{
	count_c--;
	while (count_c >= 0)
		free(ret[count_c--]);
	free(ret);
	return (NULL);
}

static int	_ft_count_char(char const *s, char c)
{
	size_t	idx_s;
	int		count_c;

	idx_s = 0;
	count_c = 0;
	while (s[idx_s] != '\0')
	{
		if (s[idx_s++] != c)
		{
			count_c++;
			while (s[idx_s] != c && s[idx_s] != '\0')
				idx_s++;
		}
	}
	return (count_c);
}

static char	**_ft_assign(char **ret, int max_r, char const *s, char c)
{
	int		idx_r;
	size_t	idx_s;
	size_t	idx_s_prev;

	idx_r = 0;
	idx_s = 0;
	while (idx_r < max_r)
	{
		while (s[idx_s] == c)
			idx_s++;
		idx_s_prev = idx_s;
		while (s[idx_s] != c && s[idx_s] != '\0')
			idx_s++;
		ret[idx_r] = (char *)malloc((idx_s - idx_s_prev + 1));
		if (ret[idx_r] == NULL)
			return (_ft_free_ret(ret, idx_r));
		ft_strlcpy(ret[idx_r], &s[idx_s_prev], idx_s - idx_s_prev + 1);
		idx_r++;
	}
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	size_t	idx_s;
	int		count_c;
	char	**ret;

	if (s == NULL)
		return (NULL);
	count_c = _ft_count_char(s, c);
	ret = (char **)malloc((count_c + 1) * sizeof(char *));
	if (ret == NULL)
		return (NULL);
	ret[count_c] = NULL;
	idx_s = 0;
	return (_ft_assign(ret, count_c, s, c));
}
