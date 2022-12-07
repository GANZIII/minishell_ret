/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyk <seonghyk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:16:51 by seonghyk          #+#    #+#             */
/*   Updated: 2022/12/05 18:16:53 by seonghyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_UTILS_H
# define MSH_UTILS_H
# include "../minishell.h"

enum e_msh_error {
	MSHERR_CMD_NOT_FOUND,
	MSHERR_CMD_PERMMISION,
	MSHERR_FILE,
	MSHERR_SYNTEX,
	MSHERR_BUILTIN_CD,
};

void	msh_error(t_token *token, enum e_msh_error error_code);
int		str_start_with(const char *str1, const char *str2);

#endif
