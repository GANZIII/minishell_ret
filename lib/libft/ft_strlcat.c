/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyk <seonghyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:14:46 by seonghyk          #+#    #+#             */
/*   Updated: 2022/03/28 17:16:09 by seonghyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	idx_d;
	size_t	idx_s;

	idx_d = 0;
	while (dst[idx_d] != '\0' && idx_d != size)
		idx_d++;
	idx_s = 0;
	if (idx_d < size)
	{
		while (idx_d + 1 < size && src[idx_s] != '\0')
		{
			dst[idx_d++] = src[idx_s++];
		}
		dst[idx_d] = 0;
	}
	else
		idx_d = size;
	while (src[idx_s] != '\0')
	{
		idx_d++;
		idx_s++;
	}
	return (idx_d);
}
