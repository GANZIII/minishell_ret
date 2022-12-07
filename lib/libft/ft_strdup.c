/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyk <seonghyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 22:48:13 by seonghyk          #+#    #+#             */
/*   Updated: 2022/03/28 17:16:09 by seonghyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t	size;
	char	*ret;

	size = 0;
	while (str[size] != 0)
		size++;
	ret = (char *)malloc(sizeof(char) * (size + 1));
	if (ret == NULL)
		return (NULL);
	size = 0;
	while (str[size] != 0)
	{
		ret[size] = str[size];
		size++;
	}
	ret[size] = '\0';
	return (ret);
}
