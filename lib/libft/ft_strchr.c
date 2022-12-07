/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyk <seonghyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 13:44:07 by seonghyk          #+#    #+#             */
/*   Updated: 2022/03/28 17:16:09 by seonghyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t		idx;
	const char	ch = (const char)c;

	idx = 0;
	while (s[idx] != ch && s[idx] != '\0')
		idx++;
	if (s[idx] == '\0' && ch != '\0')
		return (NULL);
	return ((char *)(&s[idx]));
}
