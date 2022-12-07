/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyk <seonghyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:04:06 by seonghyk          #+#    #+#             */
/*   Updated: 2022/03/28 17:16:09 by seonghyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t		idx;
	const char	ch = (const char)c;

	idx = 0;
	while (s[idx] != '\0')
		idx++;
	if (ch == '\0')
		return ((char *)&s[idx]);
	while (s[idx] != ch && idx > 0)
		idx--;
	if (idx == 0 && s[idx] != ch)
		return (NULL);
	return ((char *)(&s[idx]));
}
