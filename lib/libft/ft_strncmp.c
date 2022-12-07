/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyk <seonghyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:20:22 by seonghyk          #+#    #+#             */
/*   Updated: 2022/03/29 17:05:53 by seonghyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	idx;

	idx = 0;
	while (s1[idx] == s2[idx] && s1[idx] != '\0' && s2[idx] != '\0' && idx < n)
		idx++;
	if (n == idx)
		return (0);
	return ((unsigned char)(s1[idx]) - (unsigned char)(s2[idx]));
}
