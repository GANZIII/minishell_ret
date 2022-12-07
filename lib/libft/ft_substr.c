/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyk <seonghyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:30:28 by seonghyk          #+#    #+#             */
/*   Updated: 2022/03/29 19:52:15 by seonghyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*dst;
	unsigned int	idx_s;
	unsigned int	idx_d;
	size_t			s_len;

	if (s == NULL)
		return (NULL);
	idx_s = 0;
	s_len = ft_strlen(s);
	if (s_len <= start)
		return (ft_strdup(""));
	if (s_len - start < len)
		len = s_len - start;
	dst = (char *)malloc(len * sizeof(char) + 1);
	if (dst == NULL)
		return (NULL);
	idx_d = 0;
	while (s[start] != '\0' && idx_d < len)
		dst[idx_d++] = s[start++];
	dst[idx_d] = '\0';
	return (dst);
}
