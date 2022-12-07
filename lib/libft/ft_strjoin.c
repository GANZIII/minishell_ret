/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyk <seonghyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:41:21 by seonghyk          #+#    #+#             */
/*   Updated: 2022/03/29 19:54:29 by seonghyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	idx_s;
	size_t	idx_d;
	char	*dst;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	dst = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (dst == NULL)
		return (NULL);
	idx_s = 0;
	idx_d = 0;
	while (s1[idx_s] != '\0')
	{
		dst[idx_d++] = s1[idx_s++];
	}
	idx_s = 0;
	while (s2[idx_s] != '\0')
	{
		dst[idx_d++] = s2[idx_s++];
	}
	dst[idx_d] = '\0';
	return (dst);
}
