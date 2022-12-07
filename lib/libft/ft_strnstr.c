/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyk <seonghyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:57:55 by seonghyk          #+#    #+#             */
/*   Updated: 2022/04/25 15:15:17 by seonghyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	len_s2;
	size_t	idx;

	len_s2 = ft_strlen(s2);
	if (n == 0 && len_s2 == 0)
		return ((char *)s1);
	if (s1 == s2)
		return ((char *)s1);
	if (ft_strlen(s1) < n)
		n = ft_strlen(s1);
	idx = 0;
	while (idx + len_s2 < n)
	{
		if (ft_strncmp(s1 + idx, s2, len_s2) == 0)
			return ((char *)(s1 + idx));
		idx++;
	}
	if (ft_strncmp(s1 + idx, s2, len_s2) == 0)
		return ((char *)(s1 + idx));
	return (NULL);
}
