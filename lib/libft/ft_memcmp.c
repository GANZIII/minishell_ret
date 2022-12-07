/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyk <seonghyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:39:39 by seonghyk          #+#    #+#             */
/*   Updated: 2022/03/29 17:10:02 by seonghyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t		idx;
	const char	*s1 = (char *)str1;
	const char	*s2 = (char *)str2;

	idx = 0;
	while (idx < n && s1[idx] == s2[idx])
		idx++;
	if (n == idx)
		return (0);
	return ((unsigned char)(s1[idx]) - (unsigned char)(s2[idx]));
}
