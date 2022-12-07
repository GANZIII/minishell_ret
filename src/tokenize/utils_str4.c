/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijoo <jijoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 15:50:59 by jijoo             #+#    #+#             */
/*   Updated: 2022/12/04 17:01:58 by jijoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_div(int num, int p, char *str, int i)
{
	int		rest;

	if (num < 0)
		num *= -1;
	if (p == 1)
	{
		rest = num % 10;
		str[i] = rest + '0';
	}
	else
	{
		num /= 10;
		ft_div(num, p - 1, str, i);
	}
}

int	get_power(int *num, int *l)
{
	int	p;
	int	cp;

	cp = *num;
	p = 1;
	*l = 1;
	if (cp < 0)
	{
		(*l) += 1;
		cp *= -1;
	}
	while (cp > 9)
	{
		cp /= 10;
		p++;
	}
	*l += p;
	return (p);
}

char	*ft_itoa2(int n)
{
	char	*res;
	int		power;
	int		len;
	int		idx;

	idx = 0;
	res = malloc(10);
	power = get_power(&n, &len);
	if (n < 0)
	{
		res[0] = '-';
		idx++;
	}
	while (power)
	{
		ft_div(n, power, res, idx);
		idx++;
		power--;
	}
	res[idx] = 0;
	return (res);
}
