/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyk <seonghyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 22:13:57 by seonghyk          #+#    #+#             */
/*   Updated: 2022/03/28 17:16:09 by seonghyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*ret;
	size_t	offset;
	size_t	amount;

	amount = size * count;
	if (amount != 0 && amount / count != size)
		return (NULL);
	ret = (char *)malloc(amount);
	if (ret == NULL)
		return (NULL);
	offset = 0;
	while (sizeof(char) * offset < amount)
		ret[offset++] = 0;
	return ((void *)ret);
}
