/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyk <seonghyk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:17:43 by seonghyk          #+#    #+#             */
/*   Updated: 2022/12/05 18:17:59 by seonghyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "libft.h"
#include "../minishell.h"
#include "msh_utils.h"

void	msh_syntex_error(t_token *token, enum e_msh_error error_code)
{
	(void)error_code;
	ft_putstr_fd("msh: ", STDERR_FILENO);
	ft_putstr_fd("systax error near `", STDERR_FILENO);
	ft_putstr_fd(token->str, STDERR_FILENO);
	ft_putstr_fd("'", STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	g_shell_state.exit_status = 127;
}

void	msh_file_error(t_token *token, enum e_msh_error error_code)
{
	char	*descripton_of_error;

	(void)error_code;
	descripton_of_error = strerror(errno);
	ft_putstr_fd("msh: ", STDERR_FILENO);
	ft_putstr_fd(token->str, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(descripton_of_error, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	exit(1);
}

void	msh_builtin_cd_error(t_token *token, enum e_msh_error error_code)
{
	char	*descripton_of_error;

	(void)error_code;
	if (errno == 0)
	{
		descripton_of_error = "too many arguments";
	}
	else
	{
		descripton_of_error = strerror(errno);
	}
	ft_putstr_fd("msh: ", STDERR_FILENO);
	ft_putstr_fd(token->str, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(descripton_of_error, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	g_shell_state.exit_status = 1;
}

void	msh_cmd_error(t_token *token, enum e_msh_error error_code)
{
	char	*descripton_of_error;

	if (error_code == MSHERR_CMD_NOT_FOUND)
		descripton_of_error = "command not found";
	else
		descripton_of_error = strerror(errno);
	ft_putstr_fd("msh: ", STDERR_FILENO);
	ft_putstr_fd(token->str, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(descripton_of_error, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	if (error_code == MSHERR_CMD_NOT_FOUND)
		exit(127);
	else
		exit(126);
}

void	msh_error(t_token *token, enum e_msh_error error_code)
{
	if (error_code == MSHERR_CMD_NOT_FOUND
		||error_code == MSHERR_CMD_PERMMISION)
		msh_cmd_error(token, error_code);
	else if (error_code == MSHERR_FILE)
		msh_file_error(token, error_code);
	else if (error_code == MSHERR_SYNTEX)
		msh_syntex_error(token, error_code);
	else if (error_code == MSHERR_BUILTIN_CD)
		msh_builtin_cd_error(token, error_code);
}
