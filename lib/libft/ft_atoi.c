/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyk <seonghyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 09:57:06 by seonghyk          #+#    #+#             */
/*   Updated: 2022/03/30 16:26:51 by seonghyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	__ft_isspace(int c)
{
	if ((9 <= c && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		idx;
	long	ret;
	int		is_neg;

	idx = 0;
	while (__ft_isspace(str[idx]))
		idx++;
	is_neg = 0;
	if ((str[idx] == '-' || str[idx] == '+'))
		if (str[idx++] == '-')
			is_neg = 1;
	if (ft_isdigit(str[idx]) == 0)
		return (0);
	ret = str[idx++] - '0';
	while (ft_isdigit(str[idx]) != 0)
	{
		ret *= 10;
		ret += str[idx++] - '0';
		if (ret < 0)
			return (is_neg - 1);
	}
	if (is_neg == 1)
		return (-ret);
	return (ret);
}
