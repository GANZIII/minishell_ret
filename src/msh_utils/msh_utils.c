/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyk <seonghyk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:17:05 by seonghyk          #+#    #+#             */
/*   Updated: 2022/12/05 18:17:06 by seonghyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	str_start_with(const char *str1, const char *str2)
{
	char	*p;

	p = ft_strnstr(str1, str2, ft_strlen(str2));
	return (p == str1);
}
