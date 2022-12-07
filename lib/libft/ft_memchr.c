/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyk <seonghyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:13:17 by seonghyk          #+#    #+#             */
/*   Updated: 2022/03/29 17:11:09 by seonghyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		idx;
	const char	*str = (const char *)s;
	const char	ch = (const char)c;

	idx = 0;
	while (idx < n && str[idx] != ch)
		idx++;
	if (idx == n)
		return (NULL);
	return ((void *)&str[idx]);
}
