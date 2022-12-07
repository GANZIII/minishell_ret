/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyk <seonghyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:48:25 by seonghyk          #+#    #+#             */
/*   Updated: 2022/03/30 17:12:10 by seonghyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	int		idx;
	int		diff;
	char	*desp;
	char	*srcp;

	diff = (int)s1 - (int)s2;
	if (diff < 0)
		return (ft_memcpy(s1, s2, n));
	desp = (char *)s1;
	srcp = (char *)s2;
	if (desp == NULL && srcp == NULL)
		return (s1);
	idx = (int)n - 1;
	while (idx >= 0)
	{
		desp[idx] = srcp[idx];
		idx--;
	}
	return (s1);
}
