/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyk <seonghyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:31:24 by seonghyk          #+#    #+#             */
/*   Updated: 2022/03/30 17:12:37 by seonghyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static struct s_number_info	_ft_read_digits(int n, char *buf_digits)
{
	struct s_number_info	info;
	unsigned int			number;
	int						idx;
	int						count;

	info.is_nag = 0;
	if (n < 0)
		info.is_nag = 1;
	number = n;
	if (n < 0)
		number = -n;
	idx = 0;
	while (idx < INT_DIGITS_NUMBER)
		buf_digits[idx++] = 0;
	count = 0;
	while (number > 0)
	{
		buf_digits[count++] = number % 10 + '0';
		number /= 10;
	}
	info.count = count;
	info.buf_digits = buf_digits;
	return (info);
}

static char	*zero(void)
{
	char	*ret;

	ret = (char *)malloc(sizeof(char) * 2);
	ret[0] = '0';
	ret[1] = '\0';
	return (ret);
}

char	*ft_itoa(int n)
{
	struct s_number_info	info;
	char					*ret;
	char					buf[INT_DIGITS_NUMBER];
	int						idx;

	if (n == 0)
		return (zero());
	info = _ft_read_digits(n, buf);
	idx = 0;
	ret = (char *)malloc(sizeof(char) * (info.count + 1 + info.is_nag));
	if (ret == NULL)
		return (NULL);
	if (info.is_nag == 1)
		ret[idx++] = '-';
	ret[info.is_nag + info.count--] = '\0';
	while (info.count >= 0)
		ret[idx++] = buf[info.count--];
	return (ret);
}
