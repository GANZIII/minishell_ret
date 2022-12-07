/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyk <seonghyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 09:33:14 by seonghyk          #+#    #+#             */
/*   Updated: 2022/03/29 16:32:20 by seonghyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
	size_t	idx;
	char	*desp;
	char	*srcp;

	idx = 0;
	desp = (char *)s1;
	srcp = (char *)s2;
	if (desp == NULL && srcp == NULL)
		return (s1);
	while (idx < n)
	{
		desp[idx] = srcp[idx];
		idx++;
	}
	return (s1);
}
