/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_io_redirection_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyk <seonghyk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 14:00:53 by seonghyk          #+#    #+#             */
/*   Updated: 2022/12/04 14:01:00 by seonghyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "eval.h"
#include "libft.h"
#include "../msh_utils/msh_utils.h"

int	ppx_redirect2stdout(char *path)
{
	int	fd;

	if (unlink(path) == -1)
		if (errno != ENOENT)
			return (-1);
	fd = open(path, O_RDWR | O_CREAT, S_IRWXG | S_IRWXU);
	if (fd == -1)
	{
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (-1);
	close(fd);
	return (STDOUT_FILENO);
}

int	ppx_appending_redirect2stdout(char *path)
{
	int	fd;

	fd = open(path, O_RDWR | O_CREAT | O_APPEND, S_IRWXG | S_IRWXU);
	if (fd == -1)
	{
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (-1);
	close(fd);
	return (STDOUT_FILENO);
}

int	ppx_redirect2stdin(char *path)
{
	int	fd;

	fd = open(path, O_RDWR);
	if (fd == -1)
	{
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
		return (-1);
	close(fd);
	return (STDIN_FILENO);
}

char	*msh_alloc_expanded_line(char *line, char **envp)
{
	char	*tmp;
	int		len;
	int		idx;

	idx = 0;
	len = 0;
	while (line[idx] != '\0')
	{
		if (line[idx] == '$')
			len += search_envp(line, &idx, envp);
		else
			len++;
		if (line[idx])
			idx++;
	}
	tmp = malloc(len + 10);
	tmp[0] = '\0';
	return (tmp);
}

void	msh_expand_line(char *line, char *str, char **envp)
{
	int	idx;

	idx = -1;
	while (line[++idx] != '\0')
	{
		if (line[idx] == '$')
			ft_envp(line, &idx, str, envp);
		else
			ft_strcat_char(str, line[idx]);
	}
}
