/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyk <seonghyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:32:22 by seonghyk          #+#    #+#             */
/*   Updated: 2022/04/07 14:31:30 by seonghyk         ###   ########.fr       */
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

void	ft_putnbr_fd(int n, int fd)
{
	struct s_number_info	info;
	char					buf[INT_DIGITS_NUMBER];
	int						idx;

	if (n == 0)
	{
		ft_putchar_fd('0', fd);
		return ;
	}
	info = _ft_read_digits(n, buf);
	idx = 0;
	if (info.is_nag == 1)
		ft_putchar_fd('-', fd);
	info.count--;
	while (info.count >= 0)
		ft_putchar_fd(buf[info.count--], fd);
}
