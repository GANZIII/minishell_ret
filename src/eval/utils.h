/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyk <seonghyk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 14:01:11 by seonghyk          #+#    #+#             */
/*   Updated: 2022/12/04 14:01:13 by seonghyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

int		ppx_redirect2stdout(char *path);
int		ppx_appending_redirect2stdout(char *path);
int		ppx_redirect2stdin(char *path);
char	*msh_alloc_expanded_line(char *line, char **envp);
void	msh_expand_line(char *line, char *str, char **envp);

#endif
